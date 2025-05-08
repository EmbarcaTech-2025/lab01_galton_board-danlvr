#ifndef GALTON_SIMULATION_H
#define GALTON_SIMULATION_H

#include "include/types.h"

void galton_sim_init();
void galton_sim_add_new_ball();
void galton_sim_update(float bias);

#endif // GALTON_SIMULATION_H
