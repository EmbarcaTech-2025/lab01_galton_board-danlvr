#ifndef BUTTON_DRIVER_H
#define BUTTON_DRIVER_H

#include "pico/stdlib.h"
#include "hardware/gpio.h"

void button_driver_init(uint gpio_pin, gpio_irq_callback_t callback);
void button_driver_enable_irq(uint gpio_pin, bool enable);

#endif // BUTTON_DRIVER_H
