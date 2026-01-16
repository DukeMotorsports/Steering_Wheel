#ifndef CAN_TRANSMITTER_H
#define CAN_TRANSMITTER_H

/* ------------------------------ Includes ------------------------------ */
#include "input_handler.h"

/* ------------------------------ Macros ------------------------------ */
#define CAN_TX                      CONFIG_CAN_TX
#define CAN_RX                      CONFIG_CAN_RX
#define STEERING_WHEEL_CAN_ID       0x661

/* ------------------------------ Structs ------------------------------ */
typedef struct digital_io_data {
    uint8_t btn0 : 1; 
    uint8_t btn1 : 1; 
    uint8_t btn2 : 1; 
    uint8_t btn3 : 1; 
    uint8_t btn4 : 1; 
    uint8_t btn5 : 1; 
    uint8_t btn6 : 1; 
    uint8_t btn7 : 1; 
} digital_io_data_t;

typedef struct can_msg {
    digital_io_data_t digital_io_data; 
    uint8_t modes_status;               // Currently unused
    uint8_t screen_btns;                // Currently unused
    uint8_t clutch_pot_h; 
    uint8_t clutch_pot_l; 
    uint8_t reserved1;                  // Reserved for future use
    uint8_t reserved2; 
    uint8_t reserved3; 
} can_msg_t; 

/* ------------------------------ Public Function Declarations ------------------------------ */
void can_transmit_init(); 
void can_transmit(input_data_t *input_data); 

#endif /* CAN_TRANSMITTER_H */