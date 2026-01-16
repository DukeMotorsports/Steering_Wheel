/* ------------------------------ Includes ------------------------------ */
#include "esp_twai.h"
#include "esp_twai_onchip.h"

#include "can_transmitter.h"

/* ------------------------------ Private Global Variables ------------------------------ */
static twai_node_handle_t node_hdl = NULL;

/* ------------------------------ Public Function Definitions ------------------------------ */
void can_transmit_init() {
    twai_onchip_node_config_t node_config = {
        .io_cfg.tx = CAN_TX,                // TWAI TX GPIO pin
        .io_cfg.rx = CAN_RX,                // TWAI RX GPIO pin
        .bit_timing.bitrate = 1000000,      // 1 Bps bitrate
        .tx_queue_depth = 5,                // Transmit queue depth set to 5
        .flags.enable_self_test = true, 
    };
    // Create a new TWAI controller driver instance
    ESP_ERROR_CHECK(twai_new_node_onchip(&node_config, &node_hdl));
    // Start the TWAI controller
    ESP_ERROR_CHECK(twai_node_enable(node_hdl));
} 
void can_transmit(input_data_t *input_data) {
    can_msg_t can_msg; 
    can_msg.digital_io_data.btn0 = input_data->digital_in_0; 
    can_msg.clutch_pot_h = ((input_data->analog_in_0_mV & 0xFF00)>>8);
    can_msg.clutch_pot_l = (input_data->analog_in_0_mV & 0x00FF);

    twai_frame_t tx_msg = {
        .header.id = STEERING_WHEEL_CAN_ID,     // Message ID
        .header.ide = false,                    // Use 29-bit extended ID format
        .buffer = (uint8_t *) &can_msg,                      // Pointer to data to transmit
        .buffer_len = sizeof(can_msg),          // Length of data to transmit
    };
    ESP_ERROR_CHECK(twai_node_transmit(node_hdl, &tx_msg, 0));  // Timeout = 0: returns immediately if queue is full
} 