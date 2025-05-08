#include "app/user_interface.h"
#include "include/hal/display.h" // Para funções de desenho do display
#include "include/types.h"     // Para ViewState e current_view
#include <stdio.h>

void ui_init() {
    current_view = VIEW_SIMULATION;
    printf("UI inicializada. Visualização padrão: Simulação.\n");
}

void ui_toggle_view_state() {
    current_view = (current_view == VIEW_SIMULATION) ? VIEW_HISTOGRAM : VIEW_SIMULATION;
    printf("Visualização alterada para: %s\n", (current_view == VIEW_SIMULATION) ? "Simulação" : "Histograma");
}

// Esta função decide o que desenhar com base no estado atual da visualização.
void ui_update_view(float bias) {
    if (current_view == VIEW_SIMULATION) {
        display_draw_simulation(bias);
    }
    else { // VIEW_HISTOGRAM
        display_draw_histogram();
    }
    display_show(); // Mostra o buffer do display após desenhar o estado apropriado
}
