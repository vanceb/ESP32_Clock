// Local code
#include "main.h"
#include "clock_control.h"
#include "keyvalue.h"
#include "ota.h"


// c libraries
#include <string.h>

// Freertos
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

// ESP32 libraries
#include "esp_log.h"

// AWS IOT MQTT libraries
#include "aws_iot_config.h"
#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"

// Set the tag for logging
static const char *TAG = "clock_control";

/* CA Root certificate, device ("Thing") certificate and device
 * ("Thing") key.

   Example can be configured one of two ways:

   "Embedded Certs" are loaded from files in "certs/" and embedded into the app binary.

   "Filesystem Certs" are loaded from the filesystem (SD card, etc.)

   See example README for more details.
*/
#if defined(CONFIG_EXAMPLE_EMBEDDED_CERTS)

extern const uint8_t aws_root_ca_pem_start[] asm("_binary_aws_root_ca_pem_start");
extern const uint8_t aws_root_ca_pem_end[] asm("_binary_aws_root_ca_pem_end");
extern const uint8_t certificate_pem_crt_start[] asm("_binary_certificate_pem_crt_start");
extern const uint8_t certificate_pem_crt_end[] asm("_binary_certificate_pem_crt_end");
extern const uint8_t private_pem_key_start[] asm("_binary_private_pem_key_start");
extern const uint8_t private_pem_key_end[] asm("_binary_private_pem_key_end");

#elif defined(CONFIG_EXAMPLE_FILESYSTEM_CERTS)

static const char * DEVICE_CERTIFICATE_PATH = CONFIG_EXAMPLE_CERTIFICATE_PATH;
static const char * DEVICE_PRIVATE_KEY_PATH = CONFIG_EXAMPLE_PRIVATE_KEY_PATH;
static const char * ROOT_CA_PATH = CONFIG_EXAMPLE_ROOT_CA_PATH;

#else
#error "Invalid method for loading certs"
#endif

/**
 * @brief Default MQTT HOST URL is pulled from the aws_iot_config.h
 */
char HostAddress[255] = AWS_IOT_MQTT_HOST;

/**
 * @brief Default MQTT port is pulled from the aws_iot_config.h
 */
uint32_t port = AWS_IOT_MQTT_PORT;

/* Global variables used for mqtt communication */

/* Client details */
AWS_IoT_Client client;

/* Create a payload buffer */
char cPayload[MAX_MQTT_PAYLOAD];

/* Base mqtt topic */
char MQTT_BASE[24];

/* Full topic buffer */
char cTopic[MAX_MQTT_TOPIC];

/* Publish parameters */
IoT_Publish_Message_Params paramsQOS0;


void iot_subscribe_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
                                    IoT_Publish_Message_Params *params, void *pData) {
    ESP_LOGI(TAG, "Subscribe callback");
    ESP_LOGI(TAG, "%.*s\t%.*s", topicNameLen, topicName, (int) params->payloadLen, (char *)params->payload);
    /* Create a null terminated string from the payload */
    int i, mode;
    char *command, *key, *value;
    key_value_pair *root;
    char str_payload[params->payloadLen +1];
    for (i=0;  i<params->payloadLen; i++)
        str_payload[i] = ((char *) params->payload)[i];
    str_payload[i] = '\0';
    /* Parse the payload for key value pairs */
    key_value_pair *kv = parse_kv(str_payload);
    root = kv;
    /* Just print them out for the moment... */
    while (kv->next) {
        kv = kv->next;
        ESP_LOGI(TAG, "%s: %s", kv->key, kv->value);
    }
    /* First attempt at sending a command through mqtt */
    command = get_value(root, "cmd");
    if (*command != '/0') {
        ESP_LOGD(TAG, "Command: '%s'", command);
        /* Check for mode change */
        if (strcmp(command, "mode") == 0) {
            value = get_value(root, "mode");
            ESP_LOGI(TAG, "Setting clock display mode to %s", value);
            request_display_mode = atoi(value);
        }
        /* Check for firmware upgrade */
        if (strcmp(command, "upgrade") == 0) {
            char *firmware_url = get_value(root, "url");
            /* Check to see we have all we need for the upgrade */
            if (*firmware_url == '/0') {
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

void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data) {
    ESP_LOGW(TAG, "MQTT Disconnect");
    IoT_Error_t rc = FAILURE;

    if(NULL == pClient) {
        return;
    }

    if(aws_iot_is_autoreconnect_enabled(pClient)) {
        ESP_LOGI(TAG, "Auto Reconnect is enabled, Reconnecting attempt will start now");
    } else {
        ESP_LOGW(TAG, "Auto Reconnect not enabled. Starting manual reconnect...");
        rc = aws_iot_mqtt_attempt_reconnect(pClient);
        if(NETWORK_RECONNECTED == rc) {
            ESP_LOGW(TAG, "Manual Reconnect Successful");
        } else {
            ESP_LOGW(TAG, "Manual Reconnect Failed - %d", rc);
        }
    }
}

IoT_Error_t mqtt_init(void)
{
    /* Factory coded MAC used as ID */
    char ESP_ID[18];
    uint8_t mac[6]; 
    esp_efuse_mac_get_default(mac);
    sprintf(ESP_ID, "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    ESP_LOGD(TAG, "ESP ID: %s", ESP_ID);
    sprintf(MQTT_BASE, "%s/%s", PROJECT, (char *)ESP_ID);

    IoT_Error_t rc = FAILURE;

    IoT_Client_Init_Params mqttInitParams = iotClientInitParamsDefault;
    IoT_Client_Connect_Params connectParams = iotClientConnectParamsDefault;


    ESP_LOGI(TAG, "AWS IoT SDK Version %d.%d.%d-%s", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

    mqttInitParams.enableAutoReconnect = false; // We enable this later below
    mqttInitParams.pHostURL = HostAddress;
    mqttInitParams.port = port;

#if defined(CONFIG_EXAMPLE_EMBEDDED_CERTS)
    mqttInitParams.pRootCALocation = (const char *)aws_root_ca_pem_start;
    mqttInitParams.pDeviceCertLocation = (const char *)certificate_pem_crt_start;
    mqttInitParams.pDevicePrivateKeyLocation = (const char *)private_pem_key_start;

#elif defined(CONFIG_EXAMPLE_FILESYSTEM_CERTS)
    mqttInitParams.pRootCALocation = ROOT_CA_PATH;
    mqttInitParams.pDeviceCertLocation = DEVICE_CERTIFICATE_PATH;
    mqttInitParams.pDevicePrivateKeyLocation = DEVICE_PRIVATE_KEY_PATH;
#endif

    mqttInitParams.mqttCommandTimeout_ms = 20000;
    mqttInitParams.tlsHandshakeTimeout_ms = 5000;
    mqttInitParams.isSSLHostnameVerify = true;
    mqttInitParams.disconnectHandler = disconnectCallbackHandler;
    mqttInitParams.disconnectHandlerData = NULL;

#ifdef CONFIG_EXAMPLE_SDCARD_CERTS
    ESP_LOGI(TAG, "Mounting SD card...");
    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 3,
    };
    sdmmc_card_t* card;
    esp_err_t ret = esp_vfs_fat_sdmmc_mount("/sdcard", &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to mount SD card VFAT filesystem. Error: %s", esp_err_to_name(ret));
        abort();
    }
#endif

    rc = aws_iot_mqtt_init(&client, &mqttInitParams);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "aws_iot_mqtt_init returned error : %d ", rc);
        abort();
    }

    /* Wait for WiFI to show as connected */
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
                        false, true, portMAX_DELAY);

    connectParams.keepAliveIntervalInSec = 10;
    connectParams.isCleanSession = true;
    connectParams.MQTTVersion = MQTT_3_1_1;
    /* Client ID is set in the menuconfig of the example */
    connectParams.pClientID = CONFIG_AWS_EXAMPLE_CLIENT_ID;
    connectParams.clientIDLen = (uint16_t) strlen(CONFIG_AWS_EXAMPLE_CLIENT_ID);
    connectParams.isWillMsgPresent = false;

    ESP_LOGI(TAG, "Connecting to AWS...");
    do {
        rc = aws_iot_mqtt_connect(&client, &connectParams);
        if(SUCCESS != rc) {
            ESP_LOGE(TAG, "Error(%d) connecting to %s:%d", rc, mqttInitParams.pHostURL, mqttInitParams.port);
            vTaskDelay(1000 / portTICK_RATE_MS);
        }
    } while(SUCCESS != rc);

    /*
     * Enable Auto Reconnect functionality. Minimum and Maximum time of Exponential backoff are set in aws_iot_config.h
     *  #AWS_IOT_MQTT_MIN_RECONNECT_WAIT_INTERVAL
     *  #AWS_IOT_MQTT_MAX_RECONNECT_WAIT_INTERVAL
     */
    rc = aws_iot_mqtt_autoreconnect_set_status(&client, true);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Unable to set Auto Reconnect to true - %d", rc);
        abort();
    }

    /*
     * Subscribe to the command topic
     */
    char CMD_TOPIC[strlen(MQTT_BASE) + strlen("/cmd") + 1];
    sprintf(CMD_TOPIC, "%s%s", MQTT_BASE, "/cmd");
    const int CMD_TOPIC_LEN = strlen(CMD_TOPIC);

    ESP_LOGI(TAG, "Subscribing to: %s", CMD_TOPIC);
    rc = aws_iot_mqtt_subscribe(&client, CMD_TOPIC, CMD_TOPIC_LEN, QOS0, iot_subscribe_callback_handler, NULL);
    if(SUCCESS != rc) {
        ESP_LOGE(TAG, "Error subscribing : %d ", rc);
        abort();
    }

    /* Prepare params for mqtt publish */
    paramsQOS0.qos = QOS0;
    paramsQOS0.payload = (void *) cPayload;
    paramsQOS0.isRetained = 0;

    return rc;
}

/* The main control task
 * 
 * Sets up the mqtt connectivity and registers callbacks for
 * incoming messages and disconnect events

*/
void aws_iot_task(void *param) {
    
    int32_t i = 0;

    IoT_Error_t rc = FAILURE;

    rc = mqtt_init();

    /*
     * Prepare to send on the heartbeat topic
     */
    sprintf(cPayload, "%s : %d ", "Heartbeat: ", i);

    /*
    paramsQOS1.qos = QOS1;
    paramsQOS1.payload = (void *) cPayload;
    paramsQOS1.isRetained = 0;
    */

    char HEARTBEAT_TOPIC[64];
    sprintf(HEARTBEAT_TOPIC, "%s%s", MQTT_BASE, "/heartbeat");
    int HEARTBEAT_TOPIC_LEN = strlen(HEARTBEAT_TOPIC);

    // The main loop

    while((NETWORK_ATTEMPTING_RECONNECT == rc || NETWORK_RECONNECTED == rc || SUCCESS == rc)) {
        ESP_LOGD(TAG, "Heartbeat topic: %s", HEARTBEAT_TOPIC);

        //Max time the yield function will wait for read messages
        rc = aws_iot_mqtt_yield(&client, 100);
        if(NETWORK_ATTEMPTING_RECONNECT == rc) {
            // If the client is attempting to reconnect we will skip the rest of the loop.
            continue;
        }

        ESP_LOGD(TAG, "Stack remaining for task '%s' is %d bytes", pcTaskGetTaskName(NULL), uxTaskGetStackHighWaterMark(NULL));
        vTaskDelay(5000 / portTICK_RATE_MS);
        sprintf(cPayload, "%s : %d ", "Heartbeat", i++);
        paramsQOS0.payloadLen = strlen(cPayload);
        rc = aws_iot_mqtt_publish(&client, HEARTBEAT_TOPIC, HEARTBEAT_TOPIC_LEN, &paramsQOS0);

        /*
        sprintf(cPayload, "%s : %d ", "hello from ESP32 (QOS1)", i++);
        paramsQOS1.payloadLen = strlen(cPayload);
        rc = aws_iot_mqtt_publish(&client, TOPIC, TOPIC_LEN, &paramsQOS1);
        if (rc == MQTT_REQUEST_TIMEOUT_ERROR) {
            ESP_LOGW(TAG, "QOS1 publish ack not received.");
            rc = SUCCESS;
        }
        */
    }

    ESP_LOGE(TAG, "An error occurred in the main loop.");
    abort();
}
