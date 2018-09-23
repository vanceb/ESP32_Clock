#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt_client.h"

#include "main.h"
#include "telemetry.h"
#include "secrets.h"

static const char *TAG = "telemetry";

extern const uint8_t letsencrypt_x3_pem_start[] asm("_binary_letsencrypt_x3_pem_start");
extern const uint8_t letsencrypt_x3_pem_end[]   asm("_binary_letsencrypt_x3_pem_end");

/* Define the external tx queue */
QueueHandle_t telemetry_tx_queue;


static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            /* Subscribe to topics here */
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_subscribe(client, "/esp32clock/qos0", 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, "/esp32clock/qos1", 1);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_unsubscribe(client, "/esp32clock/qos1");
            ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
            break;
            case MQTT_EVENT_DISCONNECTED:
            /* Note disconnect here */
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            /* Post successful subscribe */
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, "/esp32clock/qos0", "data", 0, 0, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            /* Post successful unsubscribe */
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            /* Post successful publish */
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            /* Data received from mqtt server, so deal with it */
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        case MQTT_EVENT_ERROR:
            /* An mqtt error occurred */
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            break;
    }
    return ESP_OK;
}

static esp_mqtt_client_handle_t telemetry_init(void)
{
    ESP_LOGI(TAG, "Starting mqtt telemetry...");
    const esp_mqtt_client_config_t mqtt_cfg = {
        .uri = MQTT_URL,  // Defined in secrets.h
        .event_handle = mqtt_event_handler,
        .username = MQTT_USERNAME,  // Defined in secrets.h
        .password = MQTT_PASSWD,  // Defined in secrets.h
        .cert_pem = (const char *)letsencrypt_x3_pem_start,
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
    /* Create the tx queue */
    telemetry_tx_queue = xQueueCreate(TELEMETRY_MAX_TX_QUEUE, sizeof(telemetry_message_t *));
    if (telemetry_tx_queue == NULL) {
        ESP_LOGE(TAG, "Unable to create the telemetry tx queue");
        abort();
    }
    ESP_LOGI(TAG, "Successfully started mqtt telemetry");
    return client;
}

void telemetry_task(void *pvParameters)
{
    esp_mqtt_client_handle_t client = telemetry_init();
    
    /* Factory coded MAC used as ID */
    char ESP_ID[18];
    uint8_t mac[6]; 
    char base_topic[strlen(PROJECT) + strlen(ESP_ID) + 2];
    char topic[strlen(base_topic) + TELEMETRY_MAX_TOPIC_LEN];
    char message[TELEMETRY_MAX_MESSAGE_LEN + 1];
    int msg_id;
    telemetry_message_t *telemetry_message;

    esp_efuse_mac_get_default(mac);
    sprintf(ESP_ID, "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    ESP_LOGD(TAG, "ESP ID: %s", ESP_ID);
    sprintf(base_topic, "%s/%s", PROJECT, (char *)ESP_ID);

    ESP_LOGI(TAG, "Starting the telemetry transmit loop...");
    /* mqtt transmit processing loop */
    for(;;) {
        if (xQueueReceive(telemetry_tx_queue, &(telemetry_message), 15000/portTICK_PERIOD_MS)) {
            /* We have a message to process */
            strcpy(topic, base_topic);
            strncat(topic, telemetry_message->topic, TELEMETRY_MAX_TOPIC_LEN);
            strncpy(message, telemetry_message->message, TELEMETRY_MAX_MESSAGE_LEN);
            ESP_LOGI(TAG, "About to transmit telemetry...\nt: %s\nm: %s", topic, message);
            msg_id = esp_mqtt_client_publish(client, topic, message, 0, 0, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
        }
        ESP_LOGD(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));
    }
    /* Shouldn't get here */
    ESP_LOGE(TAG, "An error occurred in the telemetry transmit loop.");
    abort();
}