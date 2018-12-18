#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "APDS9960.h"
#include "gesture.h"

// Set the tag for logging
static const char *TAG = "gesture";

volatile uint16_t ambient_light;

void gestureTask ( void *pvParameters )
{
    ESP_LOGI(TAG, "Starting gesture and light sensing");

    ambient_light = 0;
    gesture_init();
    enablePower();
    enableLightSensor(0);
    //enableGestureSensor(0);
    int g;

    while (1) {
        if ( !readAmbientLight(&ambient_light) ) {
            ESP_LOGE(TAG, "Error reading from I2C");
        } 

        /* Gesture */
        /*
        if (isGestureAvailable()) {
            ESP_LOGD(TAG, "Gesture data available");
            g = readGesture();
            ESP_LOGD(TAG, "Gesture data: %d", g);
        }
        */
        vTaskDelay(100);
    }
}