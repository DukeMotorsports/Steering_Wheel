idf_component_register(SRCS "can_transmitter.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_driver_twai input_handler)
