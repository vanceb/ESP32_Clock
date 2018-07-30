#ifndef CLOCK_DISPLAY_H
#define CLOCK_DISPLAY_H

/* Manage the clock display

This contains the following functionality:

* Displaying status of the clock
* Display the time 

*/

extern void ledStrandSetup(void);
extern void blink_task(void *pvParameter);
extern void clock_display_task(void *pvParameter);

#define LEDS_GPIO 21
#define BLINK_GPIO_1 15
#define BLINK_GPIO_2 13
#define NUM_PIXELS 29

#endif