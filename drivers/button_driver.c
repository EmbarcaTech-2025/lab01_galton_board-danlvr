#include "drivers/button_driver.h"
#include <stdio.h>

void button_driver_init(uint gpio_pin, gpio_irq_callback_t callback) {
    gpio_init(gpio_pin);
    gpio_set_dir(gpio_pin, GPIO_IN);
    gpio_pull_up(gpio_pin);
    if (callback != NULL) {
        gpio_set_irq_enabled_with_callback(gpio_pin, GPIO_IRQ_EDGE_FALL, true, callback);
    }
    printf("Driver de botão inicializado para GPIO %d\n", gpio_pin);
}

void button_driver_enable_irq(uint gpio_pin, bool enable) {
    gpio_set_irq_enabled(gpio_pin, GPIO_IRQ_EDGE_FALL, enable);
    printf("IRQ de botão %s para GPIO %d\n", enable ? "ativado" : "desativado", gpio_pin);
}
