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
    io_conf.pin_bit_mask = (
        1ULL<<BTN_1 | 1ULL<<BTN_2 | 1ULL<<BTN_3 | 1ULL<<BTN_4 | 1ULL<<BTN_5 |
        1ULL<<UPSHIFT_PADDLE | 1ULL<<DOWNSHIFT_PADDLE); 
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
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, LEFT_CLUTCH, &config)); // Note: ADC1 Channels 2-4 correspond to GPIO pins 2-4
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc1_handle, RIGHT_CLUTCH, &config));

    adc_cali_curve_fitting_config_t cali_config = {
        .unit_id = ADC_UNIT_1,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_12,
    };
    ESP_ERROR_CHECK(adc_cali_create_scheme_curve_fitting(&cali_config, &adc_cali_handle));
}

void update_inputs(input_data_t *input_data) {
    // Digital inputs are active low (ie pressed btn -> Lo)
    input_data->up_shift = !gpio_get_level(UPSHIFT_PADDLE);
    input_data->down_shift = !gpio_get_level(DOWNSHIFT_PADDLE);
    input_data->left_menu_btn = !gpio_get_level(BTN_1);
    input_data->right_menu_btn = !gpio_get_level(BTN_2);
    input_data->launch_control= !gpio_get_level(BTN_4); 
    input_data->bspd_reset = !gpio_get_level(BTN_5);  

    int adc_raw, left_clutch_mV, right_clutch_mV;  
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, LEFT_CLUTCH, &adc_raw));
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc_cali_handle, adc_raw, &left_clutch_mV)); 
    ESP_ERROR_CHECK(adc_oneshot_read(adc1_handle, RIGHT_CLUTCH, &adc_raw));
    ESP_ERROR_CHECK(adc_cali_raw_to_voltage(adc_cali_handle, adc_raw, &right_clutch_mV)); 
    input_data->clutch_mV = right_clutch_mV>left_clutch_mV ? right_clutch_mV : left_clutch_mV; 
}