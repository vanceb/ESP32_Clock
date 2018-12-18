#ifndef GESTURE_H
#define GESTURE_H

#include <stdint.h>

volatile extern uint16_t ambient_light;

void gestureTask(void *pvParameters);

#endif