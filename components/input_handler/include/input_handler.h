#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

/* ------------------------------ Macros ------------------------------ */
#define BTN_1               CONFIG_SW1_GPIO_PIN
#define BTN_2               CONFIG_SW2_GPIO_PIN
#define BTN_3               CONFIG_SW3_GPIO_PIN
#define BTN_4               CONFIG_SW4_GPIO_PIN
#define BTN_5               CONFIG_SW5_GPIO_PIN
#define UPSHIFT_PADDLE      CONFIG_UPSHIFT_GPIO_PIN
#define DOWNSHIFT_PADDLE    CONFIG_DOWNSHIFT_GPIO_PIN
#define LEFT_CLUTCH         CONFIG_LEFT_CLUTCH_ADC_INPUT
#define RIGHT_CLUTCH        CONFIG_RIGHT_CLUTCH_ADC_INPUT

/* ------------------------------ Structs ------------------------------ */
typedef struct input_data {
    int up_shift;
    int down_shift;
    int left_menu_btn; 
    int right_menu_btn; 
    int bspd_reset; 
    int launch_control;
    int clutch_mV; 
} input_data_t; 

/* ------------------------------ Public Function Declarations ------------------------------ */
void input_init(void); 
void update_inputs(input_data_t *input_data); 

#endif /* INPUT_HANDLER_H */