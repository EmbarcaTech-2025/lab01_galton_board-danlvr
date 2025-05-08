#ifndef INPUT_H
#define INPUT_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

void input_init(gpio_irq_callback_t callback);
void input_handle_button_presses();

// Flags a serem verificadas pela aplicação
extern volatile bool button_a_pressed_flag;
extern volatile bool button_b_pressed_flag;

#endif // INPUT_H
