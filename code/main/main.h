#ifndef MAIN_H
#define MAIN_H

/* Some basic data */
#define PROJECT "esp32clock"
#define VERSION 1

/* The examples use simple WiFi configuration that you can set via
   'make menuconfig'.

   If you'd rather not, just change the below entries to strings with
   the config you want - ie #define EXAMPLE_WIFI_SSID "mywifissid"
*/
#define EXAMPLE_WIFI_SSID CONFIG_WIFI_SSID
#define EXAMPLE_WIFI_PASS CONFIG_WIFI_PASSWORD

/* Display modes */
extern int displayMode;

/* Color */
typedef struct color_rgb {
    int r;
    int g;
    int b;
} rgb;

typedef struct color_hsv {
    int h;
    int s;
    int v;
} hsv;

extern rgb request_color;
extern int request_display_mode;

// Some defines to improve readability
#define nullptr NULL
#define HIGH 1
#define LOW 0

// Inline functions
#define min(a, b)  ((a) < (b) ? (a) : (b))
#define max(a, b)  ((a) > (b) ? (a) : (b))
#define floor(a)   ((int)(a))
#define ceil(a)    ((int)((int)(a) < (a) ? (a+1) : (a)))

// Arduino-like functions to ease readability
extern uint32_t IRAM_ATTR millis();
extern void delay(uint32_t ms);

#endif