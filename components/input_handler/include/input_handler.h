#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

/* ------------------------------ Macros ------------------------------ */
#define GPIO_INPUT_0    CONFIG_GPIO_INPUT_0
#define ADC_INPUT_0     CONFIG_ADC_INPUT_0

/* ------------------------------ Structs ------------------------------ */
typedef struct input_data {
    int digital_in_0; 
    int analog_in_0_mV; 
} input_data_t; 

/* ------------------------------ Public Function Declarations ------------------------------ */
void input_init(void); 
void update_inputs(input_data_t *input_data); 

#endif /* INPUT_HANDLER_H */