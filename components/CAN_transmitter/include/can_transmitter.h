#ifndef CAN_TRANSMITTER_H
#define CAN_TRANSMITTER_H

/* ------------------------------ Includes ------------------------------ */
#include "input_handler.h"

/* ------------------------------ Macros ------------------------------ */
#define CAN_TX                      CONFIG_CAN_TX
#define CAN_RX                      CONFIG_CAN_RX
#define STEERING_WHEEL_CAN_ID       0x661

/* ------------------------------ Structs ------------------------------ */
typedef struct btn_data {
    uint8_t down_shift : 1; 
    uint8_t up_shift : 1; 
    uint8_t left_menu : 1; 
    uint8_t right_menu : 1; 
    uint8_t bspd_reset : 1; 
    uint8_t launch_control : 1; 
    uint8_t reserved1 : 1; 
    uint8_t reserved2 : 1; 
} btn_data_t;

typedef struct can_msg {
    btn_data_t digital_io_data; 
    uint8_t clutch_pot_h;    
    uint8_t clutch_pot_l;
    uint8_t reserved_1; 
    uint8_t reserved_2; 
    uint8_t reserved_3;                  
    uint8_t reserved_4; 
    uint8_t reserved_5; 
} can_msg_t; 

/* ------------------------------ Public Function Declarations ------------------------------ */
void can_transmit_init(); 
void can_transmit(input_data_t *input_data); 

#endif /* CAN_TRANSMITTER_H */