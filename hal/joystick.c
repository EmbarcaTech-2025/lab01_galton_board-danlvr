#include "hal/joystick.h"
#include "include/config.h"
#include "include/hal/system.h" // Para map_range
#include "drivers/adc_driver.h" // Para adc_read_raw
#include <stdio.h>
#include <stdlib.h> // Para abs
#include <math.h> // Para fabs

static uint16_t center_x; // Posição central do joystick

void joystick_init() {
    adc_driver_init(JOYSTICK_X_ADC_CHANNEL); // Inicializa o canal ADC para o joystick
    // Calibração inicial: lê o valor do joystick algumas vezes e tira a média
    uint32_t sum_x = 0;
    for (int i = 0; i < 10; i++) {
        sum_x += adc_driver_read(JOYSTICK_X_ADC_CHANNEL);
        sleep_ms(10); // Pequeno atraso entre leituras
    }
    center_x = sum_x / 10;
    printf("Joystick inicializado. Posição central X: %d\n", center_x);
}

float joystick_get_bias() {
    uint16_t raw_x = adc_driver_read(JOYSTICK_X_ADC_CHANNEL);
    int centered_x = raw_x - center_x;

    // Aplica deadzone
    if (abs(centered_x) < JOYSTICK_DEADZONE) {
        return 0.0f; // Dentro da deadzone, sem desvio
    }

    // Mapeia o valor do joystick para um intervalo de -1.0 a 1.0
    float bias = 0.0f;
    if (centered_x > 0)
    { // Para direita
        bias = map_range(raw_x, center_x + JOYSTICK_DEADZONE, RAW_X_MAX, 0.0f, 1.0f);
    }
    else
    { // Para esquerda
        bias = map_range(raw_x, RAW_X_MIN, center_x - JOYSTICK_DEADZONE, -1.0f, 0.0f);
    }

    // Limita a polarização apenas no caso de o mapeamento sair um pouco dos limites
    if (bias < -1.0f)
        bias = -1.0f;
    if (bias > 1.0f)
        bias = 1.0f;

    return bias;
}
