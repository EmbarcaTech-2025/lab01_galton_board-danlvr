#include "hal/system.h"
#include "include/config.h" // Para definições de hardware
#include "include/types.h"  // Para instância ssd1306_t
#include <stdlib.h> // Para rand() e srand()
#include <stdio.h>
#include <math.h>   // Para fabs()

// Função linear para mapear um valor de um intervalo para outro
float map_range(float value, float in_min, float in_max, float out_min, float out_max)
{
    // Evita divisão por zero
    if (fabs(in_max - in_min) < 1e-6)
    {
        return out_min + (out_max - out_min) / 2.0f; // Retorna o meio do intervalo de saída
    }
    // Calcula e retorna o valor mapeado
    return out_min + (out_max - out_min) * (value - in_min) / (in_max - in_min);
}

void system_init() {
    stdio_init_all();
    // Aguarde um pouco pela conexão serial, se necessário
    sleep_ms(2000);
    printf("Iniciando sistema...\n");

    // Seed para gerador de números aleatórios
    srand(time_us_32());

    printf("Sistema inicializado.\n");
}
