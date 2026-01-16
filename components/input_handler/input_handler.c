/* ------------------------------ Includes ------------------------------ */
#include "driver/gpio.h"

#include "hal/adc_types.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"

#include "input_handler.h"

/* ------------------------------ Private Global Variables ------------------------------ */
static adc_oneshot_unit_handle_t adc1_handle;
static adc_cali_handle_t adc_cali_handle; 

/* ------------------------------ Public Function Definitions ------------------------------ */
void input_init(void) {
    // Initialize digital inputs
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL<<GPIO_INPUT_0);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    // Initialize analog inputs
    adc_oneshot_unit_init_cfg_t init_config1 = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config1, &adc1_handle));

    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_12,
        .atten = ADC_ATTEN_DB_12,
    };
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, ADC_INPUT_0, &config)); // Note: ADC1 Channels 2-4 correspond to GPIO pins 2-4

    adc_cali_curve_fitting_config_t cali_config = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };
    ESP_ERROR_CHECK(adc_cali_create_scheme_curve_fitting(&cali_config, &adc_cali_handle));
}

void update_inputs(input_data_t *input_data) {
    input_data->digital_in_0 = gpio_get_level(GPIO_INPUT_0); 

    int adc_raw_1, analog_1_mV;  
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, ADC_INPUT_0, &adc_raw_1));
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc_cali_handle, adc_raw_1, &analog_1_mV)); 
    input_data->analog_in_0_mV = analog_1_mV; 
}