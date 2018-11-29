/* This code is based on the esp-idf OTA example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_flash_partitions.h"
#include "esp_partition.h"

#include "main.h"
#include "ota.h"
#include "wifi_manager.h"


/* Tag for log messages */
static const char *TAG = "OTA Upgrade";

/* An ota data write buffer ready to write to the flash*/
static char ota_write_data[BUFFSIZE + 1] = { 0 };

/* CA Certificate for S3 */
extern const uint8_t server_cert_pem_start[] asm("_binary_s3_ca_cert_pem_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_s3_ca_cert_pem_end");


/* Tidy up http request */
static void http_cleanup ( esp_http_client_handle_t client )
{
    esp_http_client_close(client);
    esp_http_client_cleanup(client);
}


/* Get a string version of the SHA256 hash */
void sha256_string ( const uint8_t *image_hash, char *hash_string )
{
    hash_string[HASH_LEN * 2] = 0; //terminate the string
    for (int i = 0; i < HASH_LEN; ++i) {
        sprintf ( &hash_string[i * 2], "%02x", image_hash[i] );
    }
}


/* Main task that downloads, checks and updates the firmware */
int ota_update ( char *firmware_url )
{
    ESP_LOGI ( TAG, "Starting OTA upgrade from: %s", firmware_url );

    esp_err_t err;

    /* update handle : set by esp_ota_begin(), must be freed via esp_ota_end() */
    esp_ota_handle_t update_handle = 0 ;

    const esp_partition_t *update_partition = NULL;
    const esp_partition_t *configured = esp_ota_get_boot_partition();
    const esp_partition_t *running = esp_ota_get_running_partition();

    if ( configured != running )
    {
        ESP_LOGW ( TAG, "Configured OTA boot partition at offset 0x%08x, but running from offset 0x%08x",
                 configured->address, running->address );
        ESP_LOGW ( TAG, "(This can happen if either the OTA boot data or preferred boot image become corrupted somehow.)" );
    }
    ESP_LOGI ( TAG, "Running partition type %d subtype %d (offset 0x%08x)",
             running->type, running->subtype, running->address );


    /* 
     * A request to update will come over mqtt so we should be connected
     * to wifi, but just confirm.
     */
    xEventGroupWaitBits ( wifi_manager_event_group, WIFI_MANAGER_WIFI_CONNECTED_BIT,
                        false, true, portMAX_DELAY );

    
    ESP_LOGI ( TAG, "Start to connect to upgrade server...." );
    esp_http_client_config_t config = {
        .url = firmware_url,
        .cert_pem = (char *)server_cert_pem_start,
    };
    
    esp_http_client_handle_t client = esp_http_client_init ( &config );
    if ( client == NULL ) {
        ESP_LOGE ( TAG, "Failed to initialise HTTP connection" );
        return OTA_HTTP_ERROR;
    }
    
    err = esp_http_client_open ( client, 0 );
    if ( err != ESP_OK ) {
        ESP_LOGE ( TAG, "Failed to open HTTP connection: %s", esp_err_to_name ( err ) );
        esp_http_client_cleanup ( client );
        return OTA_HTTP_ERROR;
    }
    
    esp_http_client_fetch_headers ( client );

    update_partition = esp_ota_get_next_update_partition ( NULL );

    if ( update_partition == NULL ) {
        ESP_LOGE(TAG, "Unable to get update partition");
        return OTA_PARTITION_ERROR;
    } else {
        ESP_LOGI ( TAG, "Writing to partition subtype %d at offset 0x%x",
                update_partition->subtype, update_partition->address );
    }

    err = esp_ota_begin ( update_partition, OTA_SIZE_UNKNOWN, &update_handle );
    if ( err != ESP_OK ) {
        ESP_LOGE ( TAG, "esp_ota_begin failed (%s)", esp_err_to_name ( err ) );
        http_cleanup ( client );
        return OTA_ERROR;
    }
    ESP_LOGI ( TAG, "esp_ota_begin succeeded" );

    int binary_file_length = 0;
    /*deal with all receive packet*/
    while ( 1 ) {
        int data_read = esp_http_client_read ( client, ota_write_data, BUFFSIZE );
        if ( data_read < 0 ) {
            ESP_LOGE ( TAG, "Error: SSL data read error" );
            http_cleanup ( client );
            return OTA_SSL_DATA_ERROR;
        } else if ( data_read > 0 ) {
            err = esp_ota_write ( update_handle, ( const void * ) ota_write_data, data_read );
            if (err != ESP_OK) {
                http_cleanup ( client );
                return OTA_PARTITION_WRITE_ERROR;
            }
            binary_file_length += data_read;
            ESP_LOGD ( TAG, "Written image length %d", binary_file_length );
        } else if ( data_read == 0 ) {
            ESP_LOGI ( TAG, "Connection closed,all data received" );
            break;
        }
    }

    ESP_LOGI ( TAG, "Total Write binary data length : %d", binary_file_length );

    if ( esp_ota_end ( update_handle ) != ESP_OK ) {
        ESP_LOGE ( TAG, "esp_ota_end failed!" );
        http_cleanup ( client );
        return OTA_ERROR;
    }

    /* let's set the boot partition to the new firmware */
    err = esp_ota_set_boot_partition ( update_partition );
    if ( err != ESP_OK ) {
        ESP_LOGE ( TAG, "esp_ota_set_boot_partition failed (%s)!", esp_err_to_name ( err ) );
        http_cleanup( client );
        return OTA_PARTITION_ERROR;
    }

    return OTA_OK;
}