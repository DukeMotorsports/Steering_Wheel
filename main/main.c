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
    ESP_LOGI(TAG, "Initializing Digital/Analog IO"); 
    input_init(); 
    ESP_LOGI(TAG, "Initializing CAN controller"); 
    can_transmit_init(); 

    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 100;          // Hz
    BaseType_t xWasDelayed;
    xLastWakeTime = xTaskGetTickCount ();

    // Main loop 
    while (1) {
        xWasDelayed = xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000/xFrequency));
        if (xWasDelayed) 
            ESP_LOGE(TAG, "Main loop getting interrupted"); 
        update_inputs(&input_data);
        can_transmit(&input_data); 
        // ESP_LOGI(TAG, "Clutch (mV): %d", input_data.clutch_mV); 
    }
}
