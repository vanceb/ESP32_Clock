#ifndef TELEMETRY_H
#define TELEMETRY_H

/* Define maximums */
#define TELEMETRY_MAX_TOPIC_LEN 32
#define TELEMETRY_MAX_MESSAGE_LEN 1024

/* Define a simple type for a telemetry message */
typedef struct telemetry_message {
    char *topic;
    char *message;
} telemetry_message_t;

/* Declare queue for transmit messages */
#define TELEMETRY_MAX_TX_QUEUE 10
extern QueueHandle_t telemetry_tx_queue;

/* Public functions */
void telemetry_task(void *pvParameters);

#endif