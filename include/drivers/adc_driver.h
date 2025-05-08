#ifndef ADC_DRIVER_H
#define ADC_DRIVER_H

#include "pico/stdlib.h"

void adc_driver_init();
void adc_driver_gpio_init(uint gpio);
uint16_t adc_driver_read(uint channel);
void adc_driver_select_input(uint channel);

#endif // ADC_DRIVER_H
