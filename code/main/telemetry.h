#ifndef TELEMETRY_H
#define TELEMETRY_H

/* Define maximums */
#define TELEMETRY_MAX_TOPIC_LEN 64
#define TELEMETRY_MAX_MESSAGE_LEN 256

#define HEARTBEAT_PERIOD_MS 30000

/* Define a simple type for a telemetry message */
typedef struct telemetry_message {
    char topic[TELEMETRY_MAX_TOPIC_LEN];
    char message[TELEMETRY_MAX_MESSAGE_LEN];
} telemetry_message_t;

/* Declare queue for transmit messages */
#define TELEMETRY_MAX_TX_QUEUE 10
extern QueueHandle_t telemetry_tx_queue;

/* Public functions */
void telemetry_task(void *pvParameters);
int send_telemetry(char *topic, char *message);

#endif