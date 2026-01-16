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

/* ------------------------------ Macros ------------------------------ */

#define V_REF           1.1                         // Reference voltage of SAR ADC in Volts
#define D_MAX           ((1<<ADC_BITWIDTH_12)-1)

/* ------------------------------ Private Global Variables ------------------------------ */
static const char *TAG = "main";
input_data_t input_data; 

/* ------------------------------ Public Function Definitions ------------------------------ */
void app_main(void)
{
    input_init(); 

    // Main loop 
    while (1) {
        update_inputs(&input_data); 

        ESP_LOGI(TAG, "GPIO 0 Value: %d", input_data.digital_in_1); 
        ESP_LOGI(TAG, "Analog 0 Value: %.2f", input_data.analog_in_1_mV/1000.0);

        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}
