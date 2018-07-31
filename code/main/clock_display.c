#include <time.h>
#include <sys/time.h>

#include "main.h"
#include "clock_display.h"

// ESP IDL Libraries
#include "esp_log.h"

// Neopixel library
#include "esp32_digital_led_lib.h"

// Set the tag for logging
static const char *TAG = "clock_display";

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
    ESP_LOGD(TAG, "Initialised strands");
}


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

rgb mix(rgb a, rgb b){
    rgb c;
    c.r = a.r + b.r;
    c.g = a.g + b.g;
    c.b = a.b + b.b;
    return c;
}

rgb fade(rgb color, int quotient, int divisor)
{
    color.r = (int)((long)(color.r * quotient) / divisor);
    color.g = (int)((long)(color.g * quotient) / divisor);
    color.b = (int)((long)(color.b * quotient) / divisor);
    return color;
}

void all(rgb *leds, rgb color)
{
    int i;
    for (i=0; i<NUM_PIXELS; i++){
        leds[i] = color;
    }
}

void reset_leds(rgb *leds) {
    rgb off = {0,0,0};
    all(leds, off);
}

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


void walk(rgb *leds, rgb next)
{
    int i;
    for (i=1; i<NUM_PIXELS; i++) {
        leds[i] = leds[i-1];
    }
    leds[0] = next;
}

void hypno(rgb *leds, rgb color, long hold)
{
    ESP_LOGD(TAG, "Displaying hypno");
}

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

void display_clock_simple(rgb *leds) 
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

    /* Display the clock (Simple) */
    rgb Marker_Color = {2,2,2};
    rgb Hour_Color = {16,0,16};
    rgb Minute_Color = {16,16,0};
    rgb Second_Color = {0,16,16};

    /* Clear frame buffer */
    for(i=0; i<NUM_PIXELS; i++)
        leds[i].r = leds[i].g = leds[i].b = 0;

    /* Markers */
    leds[0] = Marker_Color;
    for (i=0; i<4; i++) {
        leds[25+i] = Marker_Color;
    }
    /* Hour */
    leds[((hour)%12)+1] = Hour_Color;
    /* Minute */
    leds[((minute/5)%12)+1] = mix(Minute_Color, leds[((minute/5)%12)+1]);
    leds[((minute/5)%12)+13] = Minute_Color;
    /* Seconds */
    leds[((second/5)%12)+13] = mix(Second_Color, leds[((second/5)%12)+13]);
}


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

    /* Display the clock (Simple) */
    rgb Marker_Color = {2,2,2};
    rgb Hour_Color = {32,0,0};
    rgb Minute_Color = {0,0,32};
    rgb Second_Color = {0,32,0};

    /* Clear frame buffer */
    for(i=0; i<NUM_PIXELS; i++)
        leds[i].r = leds[i].g = leds[i].b = 0;

    /* Markers */
    leds[0] = Marker_Color;
    for (i=0; i<4; i++) {
        leds[25+i] = Marker_Color;
    }
    /* Hour */
    leds[((hour)%12)+1] = fade(Hour_Color, 60 - minute, 60);
    leds[((hour)%12)+2] = fade(Hour_Color, minute, 60);
    /* Minute */
    /* Inner ring */
    leds[((minute/5)%12)+1] = mix(fade(Minute_Color, 5 - (minute % 5), 5), leds[((minute/5)%12)+1]);
    leds[(((minute/5)+1) %12)+1] = mix(fade(Minute_Color, minute % 5, 5), leds[(((minute/5)+1)%12)+1]);
    /* Outer ring */    
    leds[((minute/5)%12)+13] = fade(Minute_Color, 5 - (minute % 5), 5);
    leds[(((minute/5)+1) %12)+13] = fade(Minute_Color, minute % 5, 5);
    /* Seconds */
    leds[((second/5)%12)+13] = mix(fade(Second_Color, 5 - (second%5), 5), leds[((second/5)%12)+13]);
    leds[(((second/5)+1)%12)+13] = mix(fade(Second_Color, second%5, 5), leds[(((second/5)+1)%12)+13]);

}


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


void clock_display_task(void *pvParameter) 
{
    int i;
    strand_t *strand = &STRANDS[0];
    rgb leds[strand->numPixels];

    rgb color;
    //int displayMode = request_display_mode;
    int displayMode = CLOCK;
    rgb request_color = {0,0,0};
    int display;

    for(;;) {
        ESP_LOGD(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));
        if ((request_color.r | request_color.g | request_color.b) == 0) 
            color = color_random();
        if (displayMode == RANDOM && (uint8_t)esp_random() < 16)
            display = (uint8_t)esp_random() % 6;
        else
            display = displayMode;

        switch (display) {
            case CLOCK:
                display_clock_fade(leds);
                delay(500);
                break;
            case SMILEY:
                smiley(leds, color);
                delay(2000);
                break;
            case WALK:
                walk(leds, color);
                delay(100);
                break;
            case HYPNO:
                hypno(leds, color, 20);
                break;
            case TWINKLE:
                twinkle(leds, 0x00800000, 2);
                break;
            case ALL:
                all(leds, color);
                delay(2000);
            default:
                ESP_LOGE(TAG, "Hit Default Display Mode - Should not happen");
                break;
        }
        /* Update the display */
        for (i=0; i<strand->numPixels; i++) {
            strand->pixels[i] = pixelFromRGB(leds[i].r, leds[i].g, leds[i].b);
        }
        digitalLeds_updatePixels(strand);
    }
}