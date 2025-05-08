#ifndef SYSTEM_H
#define SYSTEM_H

#include "pico/stdlib.h"

void system_init();
float map_range(float value, float in_min, float in_max, float out_min, float out_max);

#endif // SYSTEM_H
