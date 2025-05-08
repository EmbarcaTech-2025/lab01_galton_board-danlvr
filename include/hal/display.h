#ifndef DISPLAY_H
#define DISPLAY_H

#include "include/drivers/ssd1306.h"
#include "include/types.h" // Para utilizar ViewState

void display_init();
void display_clear();
void display_show();
void display_draw_simulation(float bias);
void display_draw_histogram();
void display_draw_pins();
void display_draw_initial_message();

#endif // DISPLAY_H
