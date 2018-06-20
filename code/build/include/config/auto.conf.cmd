deps_config := \
	/Users/vance/esp/esp-idf/components/app_trace/Kconfig \
	/Users/vance/esp/esp-idf/components/aws_iot/Kconfig \
	/Users/vance/esp/esp-idf/components/bt/Kconfig \
	/Users/vance/esp/esp-idf/components/driver/Kconfig \
	/Users/vance/esp/esp-idf/components/esp32/Kconfig \
	/Users/vance/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/Users/vance/esp/esp-idf/components/ethernet/Kconfig \
	/Users/vance/esp/esp-idf/components/fatfs/Kconfig \
	/Users/vance/esp/esp-idf/components/freertos/Kconfig \
	/Users/vance/esp/esp-idf/components/heap/Kconfig \
	/Users/vance/esp/esp-idf/components/libsodium/Kconfig \
	/Users/vance/esp/esp-idf/components/log/Kconfig \
	/Users/vance/esp/esp-idf/components/lwip/Kconfig \
	/Users/vance/esp/esp-idf/components/mbedtls/Kconfig \
	/Users/vance/esp/esp-idf/components/openssl/Kconfig \
	/Users/vance/esp/esp-idf/components/pthread/Kconfig \
	/Users/vance/esp/esp-idf/components/spi_flash/Kconfig \
	/Users/vance/esp/esp-idf/components/spiffs/Kconfig \
	/Users/vance/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/Users/vance/esp/esp-idf/components/wear_levelling/Kconfig \
	/Users/vance/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/Users/vance/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/Users/vance/esp/aws_iot_baseline/main/Kconfig.projbuild \
	/Users/vance/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/Users/vance/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
