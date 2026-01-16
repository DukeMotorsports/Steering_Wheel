idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES CAN_transmitter input_handler esp_adc esp_driver_gpio)
