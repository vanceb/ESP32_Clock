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
        .gpioNum = 21,
        .ledType = LED_WS2812B_V3,
        .brightLimit = 32,
        .numPixels = 29,
        .pixels = nullptr,
        ._stateVars = nullptr
    },
};
int STRANDCNT = sizeof(STRANDS)/sizeof(STRANDS[0]);

/* Convenience function to set up the pin for LED string
*/
void ledGpioSetup(int gpioNum) {
    // Convert ints into correct types
    gpio_num_t gpioNumNative = (gpio_num_t)(gpioNum);
    // Enable GPIO for the pins from IOMUX
    gpio_pad_select_gpio(gpioNumNative);
    // Set direction and initial value
    gpio_set_direction(gpioNumNative, GPIO_MODE_OUTPUT);
    gpio_set_level(gpioNumNative, HIGH);
    // No need to set pullup as this is an output!!
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

void smiley(strand_t* pStrand) {
    digitalLeds_resetPixels(pStrand);
    uint8_t smile[] = {1,
                       0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
                       0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
                       0, 0, 0, 0
                       }; 
    for (int i = 0; i < pStrand->numPixels; i++) {
        if (smile[i]) {
            pStrand->pixels[i] = pixelFromRGB(32, 32, 0);
        }
    }
    digitalLeds_updatePixels(pStrand);
}


void walk_task(void *pvParameter)
{
    ESP_LOGD(TAG, "Starting walk-led task");
    gpio_pad_select_gpio(LEDS_GPIO);
    gpio_set_direction(LEDS_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(LEDS_GPIO, 0);

    strand_t STRANDS[] = {
                            {.rmtChannel = 1,
                             .gpioNum = LEDS_GPIO,
                             .ledType = LED_WS2812B_V1,
                             .brightLimit = 32,
                             .numPixels = 29,
                             .pixels = NULL,
                             ._stateVars = NULL
                            },
    };
    int STRANDCNT = 1;
    if(digitalLeds_initStrands(STRANDS, STRANDCNT)) {
        ESP_LOGD(TAG, "Init Failure:  Halting...");
        while(true) {};
    }
    ESP_LOGD(TAG, "Initialised strands");

    pixelColor_t dark = pixelFromRGB(0,0,0);
    uint16_t prev = 0;
    strand_t* pStrand = &STRANDS[0];
    uint8_t r, g, b;
    smiley(pStrand);
    delay(2000);
    while(true) { 
        ESP_LOGD(TAG, "loop..");
        r = (uint8_t)esp_random() & 0x20;
        g = (uint8_t)esp_random() & 0x20;
        b = (uint8_t)esp_random() & 0x20;
        if ((r | g | b) == 0) {
            smiley(pStrand);
            delay(2000);
            continue;
        }
        digitalLeds_resetPixels(pStrand);
        pixelColor_t red = pixelFromRGB(r, g, b);
        for(uint16_t i = 0; i < pStrand->numPixels; i++) {
            pStrand->pixels[i] = red;
            pStrand->pixels[prev] = dark;
            prev = i;
            digitalLeds_updatePixels(pStrand);
            delay(200);
        }
    }
}