idf_component_register(SRCS "app_main.c"
                            "main.c"
                            "core/lib.c"
                            "core/ESP8266/basics.c"
							"core/ESP8266/wifi/wifi.c"
                            "core/ESP8266/peripherals/gpio/gpio.c"
                            "core/ESP8266/peripherals/i2c/i2c.c"
                            "core/ESP8266/peripherals/spi/spi.c"
                            "core/ESP8266/protocols/mqtt/mqtt.c"
                            "core/ESP8266/sensors/internal/internal.c"
			     			"core/ESP8266/sensors/bme280/bme280.c"
			     			"core/ESP8266/sensors/mpu6050/mpu6050.c"
			     			"core/ESP8266/sensors/bh1750/bh1750.c"
                            "core/ESP8266/sensors/acoustic/acoustic.c"
                    INCLUDE_DIRS ".")
                    
add_definitions(-DESP8266 -DMICROCONTROLLER -DMQTT -DSHELLPRINT)
