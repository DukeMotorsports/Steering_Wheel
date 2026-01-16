#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

/* ------------------------------ Structs ------------------------------ */
typedef struct input_data {
    int digital_in_1; 
    int analog_in_1_mV; 
} input_data_t; 

/* ------------------------------ Public Function Declarations ------------------------------ */
void input_init(void); 
void update_inputs(input_data_t *input_data); 

#endif /* INPUT_HANDLER_H */