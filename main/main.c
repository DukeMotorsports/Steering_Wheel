/*
 * SPDX-FileCopyrightText: 2020-2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
/* ------------------------------ Includes ------------------------------ */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#include "input_handler.h"
#include "can_transmitter.h"

/* ------------------------------ Private Global Variables ------------------------------ */
static const char *TAG = "main";
static input_data_t input_data = {0}; 

/* ------------------------------ Public Function Definitions ------------------------------ */
void app_main(void)
{
    input_init(); 
    can_transmit_init(); 

    // Main loop 
    while (1) {
        update_inputs(&input_data);
        can_transmit(&input_data); 

        // ESP_LOGI(TAG, "GPIO 0 Value: %d", input_data.digital_in_0); 
        // ESP_LOGI(TAG, "Analog 0 Value: %.2f", input_data.analog_in_0_mV/1000.0);

        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}
