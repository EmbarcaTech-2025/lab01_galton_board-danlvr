#include "drivers/adc_driver.h"
#include "hardware/adc.h"
#include <stdio.h>

void adc_driver_init() {
    adc_init();
    printf("Driver ADC inicializado.\n");
}

void adc_driver_gpio_init(uint gpio) {
    adc_gpio_init(gpio);
}

uint16_t adc_driver_read(uint channel) {
    // É uma boa prática selecionar a entrada antes de ler,
    // embora o projeto utilize um único canal.
    adc_select_input(channel);
    return adc_read();
}

void adc_driver_select_input(uint channel) {
    adc_select_input(channel);
}
