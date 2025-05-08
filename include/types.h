#ifndef TYPES_H
#define TYPES_H

#include "pico/stdlib.h"
#include "include/config.h" // Inclui config.h para MAX_BALLS e NUM_BINS
#include "include/drivers/ssd1306.h" // Necessário para ssd1306_t

// Estruturas e Enums
typedef struct
{
    float x;
    float y;
    bool active;
} Ball;

typedef enum
{
    VIEW_SIMULATION,  // Visualização da simulação
    VIEW_HISTOGRAM    // Visualização do histograma
} ViewState;

// Variáveis Globais Externas
extern ssd1306_t display;
extern Ball balls[MAX_BALLS]; // MAX_BALLS definido em config.h
extern uint16_t bins[NUM_BINS]; // NUM_BINS definido em config.h
extern uint32_t total_balls_dropped;
extern ViewState current_view;

#endif // TYPES_H
