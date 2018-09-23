#ifndef CLOCK_CONTROL_H
#define CLOCK_CONTROL_H

// AWS IOT MQTT libraries
#include "aws_iot_config.h"
#include "aws_iot_log.h"
#include "aws_iot_version.h"
#include "aws_iot_mqtt_client_interface.h"

/* Management and control of the clock

This contains the following functionality:

* Setting the time
* Setting up AWS IOT connectivity
* Report via MQTT to AWS IOT
* Act on commands received via MQTT
    - Update the config
    - Perform OTA upgrades

*/

#define MAX_MQTT_PAYLOAD 1024
#define MAX_MQTT_TOPIC 128

// Function definitions
void iot_subscribe_callback_handler(AWS_IoT_Client *pClient, char *topicName, uint16_t topicNameLen,
                                    IoT_Publish_Message_Params *params, void *pData);
void disconnectCallbackHandler(AWS_IoT_Client *pClient, void *data);
void aws_iot_task(void *param);

#endif