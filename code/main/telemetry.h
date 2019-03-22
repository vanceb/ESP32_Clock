#ifndef TELEMETRY_H
#define TELEMETRY_H

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"

/* Define maximums */
#define TELEMETRY_MAX_TOPIC_LEN 64
#define TELEMETRY_MAX_MESSAGE_LEN 256
/* Separately defined in case we want to send larger amounts of data */
#define RX_TELEMETRY_MAX_TOPIC_LEN 64
#define RX_TELEMETRY_MAX_MESSAGE_LEN 256

/* How long between heartbeat mqtt messages */
#define HEARTBEAT_PERIOD 30

/* Event Group for mqtt status */
extern EventGroupHandle_t mqtt_event_group;
#define MQTT_CONNECTED_BIT BIT0

/* Define a simple type for a telemetry message */
typedef struct telemetry_message {
    //char processed;
    char topic [ TELEMETRY_MAX_TOPIC_LEN ];
    char message [ TELEMETRY_MAX_MESSAGE_LEN ];
} telemetry_message_t;

/* Declare queue for transmit messages */
#define TELEMETRY_MAX_TX_QUEUE 10
extern QueueHandle_t telemetry_tx_queue;

/* Public functions */
void telemetry_task ( void *pvParameters );
int send_telemetry ( char *topic, char *message );

#endif