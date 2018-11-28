#include <time.h>
#include <sys/time.h>

// ESP IDF Libraries
#include "esp_log.h"
#include "esp_wifi.h"

#include "main.h"
#include "clock_display.h"
#include "telemetry.h"

// Neopixel library
#include "esp32_digital_led_lib.h"

/* Wifi manager for wifi status */
#include "wifi_manager.h"

// Set the tag for logging
static const char *TAG = "clock_display";

// Externs defined
rgb wifi_colors[4];

// Global setup for the LEDs
strand_t STRANDS[] = {
    {
        .rmtChannel = 1,
        .gpioNum = 16,
        .ledType = LED_WS2812B_V3,
        .brightLimit = 32,
        .numPixels = 29,
        .pixels = NULL,
        ._stateVars = NULL
    },
};

int STRANDCNT = sizeof(STRANDS)/sizeof(STRANDS[0]);

/* External Global Variables */
rgb request_color = {0,0,0};
int request_display_mode=0;


/* Create a color from components logarithmically 
 * Values of r, g, and b specify the shift and so 
 * the colors are 2 ^ r. etc
 */
rgb log_color(int r, int g, int b)
{
    rgb c;
    r = r>7 ? 7 : r;
    g = g>7 ? 7 : g;
    b = b>7 ? 7 : b;
    c.r = r == 0 ? 0 : 1 << r;
    c.g = g == 0 ? 0 : 1 << g;
    c.b = b == 0 ? 0 : 1 << b;
    return c;
}

/* Convenience function to set up the LED strands
*/
void ledStrandSetup(void) {
    int i;
    // GPIO setup for each strand defined above 
    for(i=0; i<STRANDCNT; i++) {
        // Convert ints into correct types
        gpio_num_t gpioNumNative = (gpio_num_t)(STRANDS[i].gpioNum);
        // Enable GPIO for the pins from IOMUX
        gpio_pad_select_gpio(gpioNumNative);
        // Set direction and initial value
        gpio_set_direction(gpioNumNative, GPIO_MODE_OUTPUT);
        gpio_set_level(gpioNumNative, HIGH);
        // No need to set pullup as this is an output!!
    }

    // Library-specific setup
    if(digitalLeds_initStrands(STRANDS, STRANDCNT)) {
        ESP_LOGE(TAG, "LED Strand Init Failure:  Halting...");
        while(true) {};
    }

    wifi_colors[0] = log_color( 7, 0, 0 );
    wifi_colors[1] = log_color( 7, 7, 0 );
    wifi_colors[2] = log_color( 0, 7, 0 );
    wifi_colors[3] = log_color( 0, 0, 7 );

    ESP_LOGD(TAG, "Initialised strands");
}

/* Mix two rgb colors */
rgb mix(rgb a, rgb b){
    rgb c;
    c.r = a.r + b.r;
    c.g = a.g + b.g;
    c.b = a.b + b.b;
    return c;
}

/* Mix 2 rgb colors logarithmically */
rgb log_mix(rgb a, rgb b)
{
    a.r |= b.r;
    a.g |= b.g;
    a.b |= b.b;
    return a;
}

/* Fade a color */
rgb fade(rgb color, int quotient, int divisor)
{
    color.r = (int)((long)(color.r * quotient) / divisor);
    color.g = (int)((long)(color.g * quotient) / divisor);
    color.b = (int)((long)(color.b * quotient) / divisor);
    return color;
}

/* Fade color logarithmically */
rgb log_fade(rgb color, unsigned int quotient, unsigned int divisor)
{
    /* Requesting off */
    if (quotient == 0) {
        color.r = color.g = color.b = 0;
        return color;
    }
    /* Requesting full brightness */
    if (divisor == 0){
        color.r = color.r > 0 ? 255 : 0;
        color.g = color.g > 0 ? 255 : 0;
        color.b = color.b > 0 ? 255 : 0;
        return color;
    }
    uint8_t shift;
    /* Increase brightness */
    if (quotient > divisor) {
        shift = quotient / divisor;
        color.r <<= shift;
        color.g <<= shift;
        color.b <<= shift;
        color.r = color.r > 255 ? 255 : color.r;
        color.g = color.g > 255 ? 255 : color.g;
        color.b = color.b > 255 ? 255 : color.b;
        return color;
    }
    /* Decrease brightness */
    if (quotient < divisor) {
        shift = divisor / quotient ;
        color.r >>= shift;
        color.g >>= shift;
        color.b >>= shift;
        color.r = color.r < 0 ? 0 : color.r;
        color.g = color.g < 0 ? 0 : color.g;
        color.b = color.b < 0 ? 0 : color.b;
        return color;
    }
    return color;
}

/* Turn on all LEDs to a apecific color */
void all(rgb *leds, rgb color)
{
    int i;
    for (i=0; i<NUM_PIXELS; i++){
        leds[i] = color;
    }
}

/* Turn all leds off */
void reset_leds(rgb *leds) {
    rgb off = {0,0,0};
    all(leds, off);
}

/* Blink the LEDs on the reverse of the board alternately */
void blink_task(void *pvParameter)
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    //ESP_LOGD(TAG, "Starting blink task");
    gpio_pad_select_gpio(BLINK_GPIO_1);
    gpio_pad_select_gpio(BLINK_GPIO_2);
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO_1, GPIO_MODE_OUTPUT);
    gpio_set_direction(BLINK_GPIO_2, GPIO_MODE_OUTPUT);
    while(1) {
        ESP_LOGD(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO_1, 0);
        gpio_set_level(BLINK_GPIO_2, 1);
        delay(1000);
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO_1, 1);
        gpio_set_level(BLINK_GPIO_2, 0);
        delay(1000);
    }
}

rgb statusColor()
{
    EventBits_t uxBits;
    uxBits = xEventGroupGetBits ( wifi_manager_event_group );

    if ( uxBits & WIFI_MANAGER_WIFI_CONNECTED_BIT ) {
        /* Wifi is connected */
        uxBits = xEventGroupGetBits ( mqtt_event_group );

        if ( uxBits & MQTT_CONNECTED_BIT ) {
            /* MQTT is connected */
            return log_color( 2, 2, 2 );

        } else {
            /* MQTT is not connected */
            return log_color( 2, 0, 2 );

        }
    } else {
        /* Wifi is not connected */
        return log_color( 2, 0, 0 );

    }
}

/* Create a wifi icon of a specified color */
void wifi_icon(rgb *leds) {
    rgb color = statusColor();

    reset_leds(leds);
    int i;
    uint8_t wifi_icon[] = {1,
                       1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
                       1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
                       0, 0, 0, 0
                       }; 
    for (i=0; i<NUM_PIXELS; i++) {
        if (wifi_icon[i]) {
            leds[i] = color;
        }
    }
}

/* Create a smiley of a specified color */
void smiley(rgb *leds, rgb color) {
    reset_leds(leds);
    int i;
    uint8_t smile[] = {1,
                       0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                       0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
                       0, 0, 0, 0
                       }; 
    for (i=0; i<NUM_PIXELS; i++) {
        if (smile[i]) {
            leds[i] = color;
        }
    }
}

/* Walk all existing colours on one place and fill 
 * the first place with a specific color 
 */
void walk(rgb *leds, rgb next)
{
    int i;
    for (i=NUM_PIXELS - 1; i>0; i--) {
        leds[i] = leds[i-1];
    }
    leds[i] = next;
}

/* Who knows... */
void hypno(rgb *leds, rgb color, long hold)
{
    ESP_LOGD(TAG, "Displaying hypno");
}

/* Create and fade random colors */
void twinkle(rgb *leds, uint32_t create, uint8_t fade)
{
    int i;
    for(i=0; i<NUM_PIXELS; i++) {
        /* Create a new twinkle */
        if(esp_random() < create)
        {
            /* Generate a random colour */
            leds[i].r = (uint8_t)esp_random();
            leds[i].g = (uint8_t)esp_random();
            leds[i].b = (uint8_t)esp_random();
        }
        /* Fade towards unlit */
        leds[i].r = (leds[i].r > fade) ? leds[i].r - fade : 0;
        leds[i].g = (leds[i].g > fade) ? leds[i].g - fade : 0;
        leds[i].b = (leds[i].b > fade) ? leds[i].b - fade : 0;
    }
}

/* Display a simple clock */
void display_clock_simple(rgb *leds) 
{
    int i;
    /* Get the local time */
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    int hour = timeinfo.tm_hour;
    int minute = timeinfo.tm_min;
    int second = timeinfo.tm_sec;

    /* Display the clock (Simple) */
    rgb Marker_Color = log_color ( 2, 2, 2 );
    rgb Hour_Color = log_color ( 7, 0, 0 );
    rgb Minute_Color = log_color ( 0, 0, 7 );
    rgb Second_Color = log_color ( 0, 7, 0 );

    /* Clear frame buffer */
    reset_leds(leds);

    /* Markers */
    Marker_Color = statusColor();

    leds[0] = Marker_Color;
    for (i=0; i<4; i++) {
        leds[25+i] = Marker_Color;
    }

    // Is time set? If not, tm_year will be (1970 - 1900).
    if (timeinfo.tm_year < (2016 - 1900)) {
        ESP_LOGE(TAG, "Time is not set, not displaying clock");
        return;
    }
    
    /* Hour */
    leds[((hour)%12)+1] = Hour_Color;
    /* Minute */
    leds[((minute/5)%12)+1] = mix(Minute_Color, leds[((minute/5)%12)+1]);
    leds[((minute/5)%12)+13] = Minute_Color;
    /* Seconds */
    leds[((second/5)%12)+13] = mix(Second_Color, leds[((second/5)%12)+13]);
}

/* Display a fading clock with logarithmic colours */
void display_clock_fade(rgb *leds)
{
    int i;
    /* Get the local time */
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    // Is time set? If not, tm_year will be (1970 - 1900).
    if (timeinfo.tm_year < (2016 - 1900)) {
        ESP_LOGE(TAG, "Time is not set, not displaying clock");
        return;
    }
    int hour = timeinfo.tm_hour;
    int minute = timeinfo.tm_min;
    int second = timeinfo.tm_sec;

    /* Set the clock colours */
    /* Display the clock (Simple) */
    rgb Marker_Color = log_color ( 2, 2, 2 );
    rgb Hour_Color = log_color ( 7, 0, 0 );
    rgb Minute_Color = log_color ( 0, 0, 7 );
    rgb Second_Color = log_color ( 0, 7, 0 );

    /* Clear frame buffer */
    reset_leds(leds);

    /* Markers */
    Marker_Color = statusColor();

    leds[0] = Marker_Color;
    for (i=0; i<4; i++) {
        leds[25+i] = Marker_Color;
    }

    /* Hour - on the inner ring */
    leds[((hour)%12)+1] = log_fade(Hour_Color, 60 - minute, 60);
    leds[((hour+1)%12)+1] = log_fade(Hour_Color, minute, 60);
    /* Minute - on both rings */
    /* Inner ring */
    leds[((minute/5)%12)+1] = log_mix(log_fade(Minute_Color, 5 - (minute % 5), 5), leds[((minute/5)%12)+1]);
    leds[(((minute/5)+1) %12)+1] = log_mix(log_fade(Minute_Color, minute % 5, 5), leds[(((minute/5)+1)%12)+1]);
    /* Outer ring */    
    leds[((minute/5)%12)+13] = log_fade(Minute_Color, 5 - (minute % 5), 5);
    leds[(((minute/5)+1) %12)+13] = log_fade(Minute_Color, minute % 5, 5);
    /* Seconds - on the outer ring */
    leds[((second/5)%12)+13] = log_mix(log_fade(Second_Color, 5 - (second%5), 5), leds[((second/5)%12)+13]);
    leds[(((second/5)+1)%12)+13] = log_mix(log_fade(Second_Color, second%5, 5), leds[(((second/5)+1)%12)+13]);
}


/* Generate a random colour */
rgb color_random()
{
    rgb c = {0,0,0};
    while ((c.r | c.g | c.b) == 0) 
    {
        /* Generate a random colour */
        c.r = (uint8_t)esp_random() & 0x2F;
        c.g = (uint8_t)esp_random() & 0x2F;
        c.b = (uint8_t)esp_random() & 0x2F;
    }
    return c;
}

/* Generate a random logarithmic color */
rgb log_color_random()
{
    rgb c = {0,0,0};
    while ((c.r | c.g | c.b) == 0) 
    {
        /* Generate a random colour */
        c.r = 1 << ((uint8_t)esp_random() & 0x07);
        c.g = 1 << ((uint8_t)esp_random() & 0x07);
        c.b = 1 << ((uint8_t)esp_random() & 0x07);
    }
    return c;
}

void brightness ( rgb *leds, uint8_t brightness )
{
    int i;
    /* Limit brightness */
    brightness = brightness > 7 ? 7 : brightness;
    /* Invert brightness for scaling */
    brightness = 7 - brightness;
    
    for ( i=0; i<NUM_PIXELS; i++ ) 
    {
        leds[i].r = leds[i].r == 0 ? 0 : ( leds[i].r > ( 1 << brightness ) ? leds[i].r >> brightness : 1);
        leds[i].g = leds[i].g == 0 ? 0 : ( leds[i].g > ( 1 << brightness ) ? leds[i].g >> brightness : 1);
        leds[i].b = leds[i].b == 0 ? 0 : ( leds[i].b > ( 1 << brightness ) ? leds[i].b >> brightness : 1);
    }
}

/* Main task that controls the display */
void clock_display_task(void *pvParameter) 
{
    int i;
    /* Create the pointer to the strand used by the library */
    strand_t *strand = &STRANDS[0];
    /* Create a display buffer used by our code */
    rgb leds[strand->numPixels];

    rgb color;

    //int displayMode = request_display_mode;

    int display;

    /* The main forever loop */
    for(;;) {
        /* Report the stack high water mark */
        ESP_LOGD(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));
        if ((request_color.r | request_color.g | request_color.b) == 0) 
            color = color_random();
        if (request_display_mode == 0 && (uint8_t)esp_random() < 4) {
            display = (uint8_t)esp_random() % 6;
            ESP_LOGD(TAG, "Set random display mode to %d", display);
        } else {
            display = request_display_mode;
        }
        switch (display) {
            case 0:
                wifi_icon(leds);
                delay ( 500 );
                break;
            case 1:
                display_clock_fade(leds);
                delay(500);
                break;
            case 2:
                display_clock_simple(leds);
                delay(500);
                break;
            case 3:
                walk(leds, color);
                delay(100);
                break;
            case 4:
                smiley(leds, color);
                delay(2000);
                break;
            case 5:
                twinkle(leds, 0x00800000, 20);
                delay(20);
                break;
            case 6:
                all(leds, color);
                delay(2000);
                break;
            default:
                ESP_LOGE(TAG, "Hit Default Display Mode - Should not happen");
                break;
        }
        /* Update the display */
        brightness ( leds, 7 );
        for (i=0; i<strand->numPixels; i++) {
            strand->pixels[i] = pixelFromRGB(leds[i].r, leds[i].g, leds[i].b);
        }
        digitalLeds_updatePixels(strand);
    }
}