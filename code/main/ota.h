#ifndef OTA_H
#define OTA_H

#define BUFFSIZE 1024
#define HASH_LEN 32 /* SHA-256 digest length */

typedef enum ota_returncodes {
    OTA_OK,
    OTA_HTTP_ERROR,
    OTA_PARTITION_ERROR,
    OTA_PARTITION_WRITE_ERROR,
    OTA_SHA256_MISMATCH,
    OTA_SSL_DATA_ERROR,
    OTA_ERROR
} ota_error_t;

int ota_update(char *firmware_url);

#endif