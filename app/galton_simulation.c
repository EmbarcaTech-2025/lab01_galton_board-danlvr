#include "app/galton_simulation.h"
#include "include/config.h"
#include "include/types.h"
#include <stdio.h>
#include <stdlib.h> // Para utilizar rand()
#include <math.h>   // Para utilizar fabs(), floor()

void galton_sim_init() {
    for (int i = 0; i < MAX_BALLS; ++i) {
        balls[i].active = false;
    }
    for (int i = 0; i < NUM_BINS; ++i) {
        bins[i] = 0;
    }
    total_balls_dropped = 0;
    printf("Simulação de Galton inicializada.\n");
}

void galton_sim_add_new_ball() {
    for (int i = 0; i < MAX_BALLS; ++i) {
        if (!balls[i].active) {
            balls[i].x = SSD1306_WIDTH / 2.0f; // Inicializa no centro
            balls[i].y = 0.0f;
            balls[i].active = true;
            printf("Bola %d adicionada ao topo.\n", i);
            return; // Adicione apenas uma bola de cada vez
        }
    }
    printf("Número máximo de bolas atingido!\n");
}

void galton_sim_update(float bias) {
    for (int i = 0; i < MAX_BALLS; ++i) {
        if (balls[i].active) {
            balls[i].y += 1.0f; // Movimento simples para baixo

            bool collision_handled = false;
            for (int row = 0; row < NUM_PIN_ROWS; ++row) {
                float row_y = PIN_ROW_START_Y + row * PIN_ROW_SPACING;

                if (balls[i].y >= row_y && balls[i].y < row_y + 1.0f) {
                    float row_width = (PINS_PER_ROW(row) - 1) * PIN_HORIZONTAL_SPACING;
                    float row_start_x = (SSD1306_WIDTH - row_width) / 2.0f;

                    for (int pin_idx = 0; pin_idx < PINS_PER_ROW(row); ++pin_idx) {
                        float pin_x = row_start_x + pin_idx * PIN_HORIZONTAL_SPACING;

                        if (fabs(balls[i].x - pin_x) < PIN_HORIZONTAL_SPACING / 2.0f) {
                            int random_choice = rand() % 100;
                            int threshold = 50 + (int)(bias * 40.0f);
                            if (threshold < 5) threshold = 5;
                            if (threshold > 95) threshold = 95;

                            if (random_choice < threshold) {
                                balls[i].x += PIN_HORIZONTAL_SPACING / 2.0f;
                            } else {
                                balls[i].x -= PIN_HORIZONTAL_SPACING / 2.0f;
                            }
                            balls[i].y = row_y + 1.0f; // Move a bola para baixo do pino para evitar colisões múltiplas na mesma linha
                            collision_handled = true; // Marca que a colisão foi tratada para esta bola
                            goto next_ball_update; // Pula para a próxima atualização da bola
                        }
                    }
                }
            }

        next_ball_update:
            if (balls[i].y >= BOTTOM_Y) {
                if (balls[i].x < 0) balls[i].x = 0;
                if (balls[i].x >= SSD1306_WIDTH) balls[i].x = SSD1306_WIDTH - 1;

                int bin_index = (int)floor(balls[i].x / BIN_WIDTH);
                if (bin_index < 0) bin_index = 0;
                if (bin_index >= NUM_BINS) bin_index = NUM_BINS - 1;

                bins[bin_index]++;
                total_balls_dropped++;
                printf("Bola %d finalizou na canaleta %d (x=%.1f). Contagem da canaleta: %d, Total: %lu\n", i, bin_index, balls[i].x, bins[bin_index], total_balls_dropped);
                balls[i].active = false;
            }

            // Garante que a bola permaneça dentro dos limites horizontais da tela
            if (balls[i].x < BALL_RADIUS) balls[i].x = BALL_RADIUS;
            if (balls[i].x > SSD1306_WIDTH - 1 - BALL_RADIUS) balls[i].x = SSD1306_WIDTH - 1 - BALL_RADIUS;
        }
    }
}
