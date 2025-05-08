#include <stdio.h>
#include "pico/stdlib.h"

#include "include/config.h"
#include "include/types.h"

// Includes HAL
#include "include/hal/system.h"
#include "include/hal/display.h"
#include "include/hal/joystick.h"
#include "include/hal/input.h"

// Includes App
#include "include/app/galton_simulation.h"
#include "include/app/user_interface.h"

// Definição das variáveis globais que foram declaradas como externas em types.h
ssd1306_t display;
Ball balls[MAX_BALLS];
uint16_t bins[NUM_BINS];
uint32_t total_balls_dropped = 0;
ViewState current_view;

// Função principal
int main()
{
    // Inicialização de HAL e Drivers
    system_init();      // Inicialização básica do sistema (stdio, seed aleatório)
    display_init();     // Inicialização do I2C e Display SSD1306
    joystick_init();    // Inicialização do ADC para o Joystick
    input_init(NULL);   // Inicialização dos botões e suas interrupções (passa NULL para usar o callback interno do input.c)
    
    // Inicialização dos módulos da Aplicação
    galton_sim_init();  // Inicializa o estado da simulação (bolas, canaletas)
    ui_init();          // Inicializa o estado da interface do usuário (visualização padrão)

    printf("Todos os módulos inicializados. Iniciando loop principal...\n");

    while (true)
    {
        input_handle_button_presses(); // Processa as flags de botões setadas por interrupções

        float bias = joystick_get_bias(); // Lê o joystick para o desvio

        // Atualiza a lógica da simulação apenas se estiver na visualização de simulação
        if (current_view == VIEW_SIMULATION) 
        {
            galton_sim_update(bias);
        }
        
        // Atualiza a tela (desenha simulação ou histograma)
        ui_update_view(bias); // A UI decide o que mostrar com base no current_view

        sleep_ms(LOOP_DELAY_MS); // Controla a velocidade da simulação/atualização
    }
    return 0; // Nunca alcançado
}