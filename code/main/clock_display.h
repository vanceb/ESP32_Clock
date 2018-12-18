#ifndef CLOCK_DISPLAY_H
#define CLOCK_DISPLAY_H

/* Manage the clock display

This contains the following functionality:

* Displaying status of the clock
* Display the time 

*/

#define LEDS_GPIO 21
#define BLINK_GPIO_1 15
#define BLINK_GPIO_2 13
#define NUM_PIXELS 29


/* Brighness values for LEDs */
#define MIN_BRIGHTNESS 0
#define MAX_BRIGHTNESS 255
/* Values for the ambient light sensor */
#define MIN_AMBIENT 0
#define MAX_AMBIENT 50

extern void ledStrandSetup(void);
extern void displayWifi(int state);
extern void blink_task(void *pvParameter);
extern void clock_display_task(void *pvParameter);

// Define colors
#define RED { 255, 0, 0 };
#define GREEN { 0, 255, 0 };
#define BLUE { 0, 0, 255 };
#define MAGENTA { 255, 0, 255 };
#define YELLOW { 255, 255, 0 };
#define CYAN { 0, 255, 255 };
#define BLACK { 0, 0, 0 };
#define WHITE { 255, 255, 255 };


#endif