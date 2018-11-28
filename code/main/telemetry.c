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
#include "kv.h"
#include "ota.h"

#define UPTIME_CHARS 16 // The length of the uptime string in characters

static const char *TAG = "telemetry";
EventGroupHandle_t mqtt_event_group = NULL;
const int MQTT_CONNECTED_BIT = BIT0;

extern const uint8_t letsencrypt_x3_pem_start[] asm("_binary_letsencrypt_x3_pem_start");
extern const uint8_t letsencrypt_x3_pem_end[]   asm("_binary_letsencrypt_x3_pem_end");

/* Create a reference to the tx queue */
QueueHandle_t telemetry_tx_queue;

/* Declare base topic */
char base_topic[64];

/* Define creators and destructors for telemetry messages */
telemetry_message_t *newMessage()
{
    ESP_LOGD(TAG, "Creating a new telemetry message. Heap available: %ul", esp_get_free_heap_size());
    telemetry_message_t *msg = (telemetry_message_t *) malloc(sizeof(telemetry_message_t));
    if (msg == NULL) {
        ESP_LOGE(TAG, "Unable to allocate heap for telemetry structure"); 
        return NULL;
    }
    ESP_LOGD(TAG, "Successfully created a new telemetry message. Heap left: %ul", esp_get_free_heap_size());
    return msg;
}

void freeMessage(telemetry_message_t *msg)
{
    if (msg != NULL) {
        ESP_LOGD(TAG, "About to free message.  Heap available: %ul", esp_get_free_heap_size());
        free(msg);
        ESP_LOGD(TAG, "Freed memory.  Heap available: %ul", esp_get_free_heap_size());
    }
}

int uptime(char *uptime_str, int max_chars)
{
    int days, hours, minutes, seconds;
    unsigned long uptime_secs = clock_ms() / 1000;
    days = uptime_secs / (60 * 60 * 24);
    uptime_secs -= days * (60 * 60 * 24);
    hours = uptime_secs / (60 * 60);
    uptime_secs -= hours * (60 * 60);
    minutes = uptime_secs / 60;
    seconds = uptime_secs - (minutes * 60);
    return snprintf(uptime_str, max_chars, "%d:%02d:%02d:%02d", days, hours, minutes, seconds);
}
 

void parse_command(char *buffer) {

    /* Parse the payload for key value pairs */
    kv *root = parseKv(buffer);
    kv *cursor = root;

    /* Just print them out for the moment... */
    char serialise[1024]; // Buffer to hold serialised output
    serialiseKv ( root, serialise, 1024 );
    ESP_LOGD ( TAG, "Parsed KV\n%s", serialise );

    /* First attempt at sending a command through mqtt */
    char *command = getValue(root, "cmd");
    char *value = NULL;
    if ( ( command != NULL ) && ( *command != '\0' ) ) {
        ESP_LOGD(TAG, "Command: '%s'", command);
        /* Check for mode change */
        if (strcmp(command, "mode") == 0) {
            value = getValue(root, "mode");
            ESP_LOGI(TAG, "Setting clock display mode to %s", value);
            request_display_mode = atoi(value);
        }
        /* Check for firmware upgrade */
        if (strcmp(command, "upgrade") == 0) {
            char *firmware_url = getValue(root, "url");
            /* Check to see we have all we need for the upgrade */
            if (firmware_url == NULL || *firmware_url == '\0') {
                ESP_LOGE(TAG, "Received mqtt upgrade request without url");
            } else {
                /* We can start the upgrade */
                ESP_LOGI(TAG, "Starting OTA upgrade from: %s", firmware_url);
                ota_error_t err;
                err = ota_update(firmware_url);
                if (err != OTA_OK) {
                    ESP_LOGE(TAG, "Error performing OTA upgrade - Not upgraded");
                } else {
                    /* OTA upgrade was successful */
                    ESP_LOGI(TAG, "OTA upgrade successful. Prepare to restart system!");
                    esp_restart();
                }
            }
        }
    } else {
        ESP_LOGE(TAG, "Received mqtt data without a command");
    }

}


static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    int chars_copied;
    char sub_topic[TELEMETRY_MAX_TOPIC_LEN + strlen(base_topic)];
    char rx_topic[RX_TELEMETRY_MAX_TOPIC_LEN];
    char rx_msg[RX_TELEMETRY_MAX_MESSAGE_LEN];
    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            xEventGroupSetBits(mqtt_event_group, MQTT_CONNECTED_BIT);
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            /* Subscribe to topics here */
            strcpy(sub_topic, base_topic);
            strncat(sub_topic, "cmd", TELEMETRY_MAX_TOPIC_LEN);
            msg_id = esp_mqtt_client_subscribe(client, sub_topic, 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_DISCONNECTED:
            xEventGroupClearBits(mqtt_event_group, MQTT_CONNECTED_BIT);
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            /* Post successful subscribe */
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
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
            /* Sanity check on message lengths */
            if (event->topic_len > RX_TELEMETRY_MAX_TOPIC_LEN - 1) {
                ESP_LOGE(TAG, "Received message topic too long: Rx:%dm Max:%d",
                        event->topic_len, RX_TELEMETRY_MAX_TOPIC_LEN - 1);
                send_telemetry("error", "Rx topic too long!");
                return ESP_FAIL;
            }
            if (event->topic_len > RX_TELEMETRY_MAX_MESSAGE_LEN - 1) {
                ESP_LOGE(TAG, "Received message msg too long: Rx:%dm Max:%d",
                        event->data_len, RX_TELEMETRY_MAX_MESSAGE_LEN - 1);
                send_telemetry("error", "Rx msg too long!");
                return ESP_FAIL;
            }
            /* Get the topic and payload as c strings */
            strncpy(rx_topic, event->topic, event->topic_len);
            rx_topic[event->topic_len] = '\0';
            strncpy(rx_msg, event->data, event->data_len);
            rx_msg[event->data_len] = '\0';
            printf("TOPIC=%s\r\n", rx_topic);
            printf("DATA=%s\r\n", rx_msg);
            send_telemetry("echo", rx_msg);
            parse_command(rx_msg);
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
    /* Create the event group for signalling state */
    mqtt_event_group = xEventGroupCreate();

    ESP_LOGI(TAG, "Starting mqtt telemetry...");
    const esp_mqtt_client_config_t mqtt_cfg = {
        .uri = MQTT_URL,  // Defined in secrets.h
        .event_handle = mqtt_event_handler,
        .username = MQTT_USERNAME,  // Defined in secrets.h
        .password = MQTT_PASSWD,  // Defined in secrets.h
        .cert_pem = (const char *)letsencrypt_x3_pem_start,
    };

    /* Create the mqtt client from the config */
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
    
    /* Define base topic */
    char ESP_ID[18];
    uint8_t mac[6]; 

    /* Factory coded MAC used as ID */
    esp_efuse_mac_get_default(mac);
    sprintf(ESP_ID, "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    ESP_LOGD(TAG, "ESP ID: %s", ESP_ID);
    sprintf(base_topic, "%s/%s/", PROJECT, (char *)ESP_ID);
    ESP_LOGI(TAG, "Base mqtt topic set as: %s", base_topic);

    /* Create the tx queue */
    telemetry_tx_queue = xQueueCreate(TELEMETRY_MAX_TX_QUEUE, sizeof(telemetry_message_t *));
    if (telemetry_tx_queue == NULL) {
        ESP_LOGE(TAG, "Unable to create the telemetry tx queue");
        abort();
    }
    ESP_LOGI(TAG, "Successfully started mqtt telemetry");
    return client;
}


BaseType_t send_telemetry(char *topic, char *message)
{
    telemetry_message_t *telemetry = newMessage();
    if (telemetry == NULL) {
        ESP_LOGE(TAG, "Unable to allocate memory for telemetry message");
        abort();
    }
    ESP_LOGD(TAG, "About to copy %s %s to message", topic, message);
    /* Sanity check topic length */
    if (strlen(base_topic) + strlen(topic) > TELEMETRY_MAX_TOPIC_LEN) {
        ESP_LOGE(TAG, "Send Telemetry topic length too long: %d, Max: %d",
                 strlen(base_topic) + strlen(topic), TELEMETRY_MAX_TOPIC_LEN);
        return -1; 
    } 
    /* Sanity check message length */
    if (strlen(message) > TELEMETRY_MAX_MESSAGE_LEN) {
        ESP_LOGE(TAG, "Send Telemetry message length too long: %d, Max: %d",
                 strlen(message), TELEMETRY_MAX_MESSAGE_LEN);
        return -1; 
    } 
    /* Prepare to queue message */
    strcpy(telemetry->topic, base_topic);
    strncat(telemetry->topic, topic, TELEMETRY_MAX_TOPIC_LEN - 1);
    telemetry->topic[strlen(base_topic) + strlen(topic)] = '\0';
    strncpy(telemetry->message, message, TELEMETRY_MAX_MESSAGE_LEN - 1);
    telemetry->message[strlen(message)] = '\0';
    ESP_LOGD(TAG, "Queueing:\nt: %s\nm: %s", telemetry->topic, telemetry->message);
    //return xQueueSend(telemetry_tx_queue, (void *) telemetry, 0);
    return xQueueSend(telemetry_tx_queue, (void *) &telemetry, 0);
}


void telemetry_task(void *pvParameters)
{
    esp_mqtt_client_handle_t client = telemetry_init();

    int msg_id;
    char uptime_str[UPTIME_CHARS];
    telemetry_message_t *telemetry_message;
    char hb_msg[TELEMETRY_MAX_MESSAGE_LEN];
    unsigned long last_hb = 0;
    EventBits_t bits;

    /* Queue a startup messgae */
    send_telemetry("status", "Startup mqtt telemetry");
    

    ESP_LOGI(TAG, "Starting the telemetry transmit loop...");
    /* mqtt transmit processing loop */
    for(;;) {
        bits = xEventGroupWaitBits(mqtt_event_group, MQTT_CONNECTED_BIT,
                            false, true, 0);
        if (bits & MQTT_CONNECTED_BIT){
            /* We are connected to mqtt broker */
            ESP_LOGD(TAG, "Messages in queue: %d", uxQueueMessagesWaiting(telemetry_tx_queue));
            if (xQueueReceive(telemetry_tx_queue, &(telemetry_message), 15000/portTICK_PERIOD_MS)) {
                /* We got a message from the queue so send it */
                ESP_LOGD(TAG, "About to transmit telemetry...\nt: %s\nm: %s", telemetry_message->topic, telemetry_message->message);
                msg_id = esp_mqtt_client_publish(client, telemetry_message->topic, telemetry_message->message, 0, 0, 0); 
                ESP_LOGI(TAG, "Published:\nt: %s\nm: %s", telemetry_message->topic, telemetry_message->message);
                /* Free the message memory */
                freeMessage(telemetry_message);
            }
            ESP_LOGD(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));

            /* Send heartbeat */
            if (clock_ms() > last_hb + HEARTBEAT_PERIOD_MS) {
                last_hb = clock_ms();
                uptime(uptime_str, UPTIME_CHARS);
                sprintf(hb_msg, "uptime %s\nversion %d", uptime_str, VERSION);
                send_telemetry("heartbeat", hb_msg);
            }
        } else {
            /* We are not connected to the mqtt broker */
            ESP_LOGI(TAG, "Not connected to the mqtt broker, waiting for reconnect...");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

    }
    /* Shouldn't get here */
    ESP_LOGE(TAG, "An error occurred in the telemetry transmit loop.");
    abort();
}