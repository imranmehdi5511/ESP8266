idf_component_register(SRCS "app_main.c"
                            "main.c"
                            "core/lib.c"
                            "core/json/decoder-i2t-json.c"
                            "core/ESP8266/basics.c"
							"core/ESP8266/wifi/wifi.c"
							"core/ESP8266/output/relay/relay.c"
                            "core/ESP8266/peripherals/gpio/gpio.c"
                            "core/ESP8266/peripherals/i2c/i2c.c"
                            "core/ESP8266/peripherals/spi/spi.c"
                            "core/ESP8266/protocols/http/http.c"
                    INCLUDE_DIRS ".")
                    
add_definitions(-DESP8266 -DMICROCONTROLLER -DHTTP -DSHELLPRINT -DEXAMPLE)
