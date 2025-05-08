#include "hal/input.h"
#include "include/config.h"
#include "include/types.h" // Para current_view
#include "include/drivers/button_driver.h"
#include "app/galton_simulation.h" // Para add_new_ball
#include "app/user_interface.h" // Para ui_toggle_view
#include <stdio.h>

// Estado de debounce do botão
static volatile uint32_t last_press_time_a = 0;
static volatile uint32_t last_press_time_b = 0;
volatile bool button_a_pressed_flag = false;
volatile bool button_b_pressed_flag = false;

// Callback para interrupções de GPIO (botões)
static void gpio_button_callback(uint gpio, uint32_t events) {
    if (events == GPIO_IRQ_EDGE_FALL) {
        uint32_t now = time_us_32();
        if (gpio == BUTTON_A_PIN) {
            if ((int32_t)(now - last_press_time_a) > DEBOUNCE_DELAY_MS * 1000 || last_press_time_a == 0) {
                button_a_pressed_flag = true;
                last_press_time_a = now;
            }
        }
        else if (gpio == BUTTON_B_PIN) {
            if ((int32_t)(now - last_press_time_b) > DEBOUNCE_DELAY_MS * 1000 || last_press_time_b == 0) {
                button_b_pressed_flag = true;
                last_press_time_b = now;
            }
        }
    }
}

void input_init(gpio_irq_callback_t callback_param) {
    // Se um callback específico não for fornecido, usa o callback interno de botão.
    gpio_irq_callback_t callback_to_use = (callback_param != NULL) ? callback_param : gpio_button_callback;

    button_driver_init(BUTTON_A_PIN, callback_to_use);
    button_driver_init(BUTTON_B_PIN, callback_to_use);
    printf("Sistema de entrada (botões) inicializado.\n");
}

// Função chamada no loop principal do app para processar as flags dos botões.
void input_handle_button_presses() {
    if (button_a_pressed_flag) {
        if (current_view == VIEW_SIMULATION) { // Só adiciona bola na tela de simulação
            galton_sim_add_new_ball();
        }
        button_a_pressed_flag = false; 
    }
    if (button_b_pressed_flag) {
        ui_toggle_view_state(); // A UI lida com a lógica de alternância
        button_b_pressed_flag = false; 
    }
}
