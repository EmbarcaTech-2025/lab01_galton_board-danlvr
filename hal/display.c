#include "hal/display.h"
#include "include/config.h"
#include "include/types.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <stdio.h>
#include <string.h> // Para sprintf

void display_init() {
    // Inicialização I2C
    i2c_init(I2C_PORT, 400 * 1000); // 400kHz
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);

    // Inicialização do display SSD1306
    if (!ssd1306_init(&display, SSD1306_WIDTH, SSD1306_HEIGHT, 0x3C, I2C_PORT))
    {
        printf("Falha ao inicializar SSD1306\n");
        while (1)
            ; // Parar em caso de erro
    }
    ssd1306_clear(&display);
    ssd1306_show(&display);
    printf("Display SSD1306 inicializado e limpo.\n");
    display_draw_initial_message();
}

void display_draw_initial_message(){
    ssd1306_clear(&display);
    // Exibir mensagem inicial
    ssd1306_draw_string(&display, 5, 5, 1, "Carregando");
    ssd1306_draw_string(&display, 5, 20, 1, "Galton Board...");
    ssd1306_show(&display);
    sleep_ms(1000); // Dê tempo para o usuário ver a mensagem
}

void display_clear() {
    ssd1306_clear(&display);
}

void display_show() {
    ssd1306_show(&display);
}

// Desenha os pinos do Galton Board
void display_draw_pins()
{
    for (int row = 0; row < NUM_PIN_ROWS; ++row)
    {
        int num_pins_in_row = PINS_PER_ROW(row);
        float row_y = PIN_ROW_START_Y + row * PIN_ROW_SPACING;
        float row_width = (num_pins_in_row - 1) * PIN_HORIZONTAL_SPACING;
        float row_start_x = (SSD1306_WIDTH - row_width) / 2.0f;

        for (int pin_idx = 0; pin_idx < num_pins_in_row; ++pin_idx)
        {
            float pin_x = row_start_x + pin_idx * PIN_HORIZONTAL_SPACING;

            int px = (int)pin_x;
            int py = (int)row_y;

            // Checa se o pixel está dentro dos limites do display
            if (px >= 0 && px < SSD1306_WIDTH && py >= 0 && py < SSD1306_HEIGHT)
            {
                ssd1306_draw_pixel(&display, px, py);
            }
        }
    }
}

// Desenha a tela de simulação
void display_draw_simulation(float bias)
{
    display_clear();

    // Desenha pinos
    display_draw_pins();

    // Desenha canaletas
    for (int i = 0; i <= NUM_BINS; ++i)
    {
        int x = (int)(i * BIN_WIDTH);
        if (x >= SSD1306_WIDTH)
            x = SSD1306_WIDTH - 1; // Limita a borda
        ssd1306_draw_line(&display, x, BOTTOM_Y, x, SSD1306_HEIGHT - 1);
    }
    ssd1306_draw_line(&display, 0, BOTTOM_Y, SSD1306_WIDTH - 1, BOTTOM_Y); // Linhas separando canaletas dos pinos

    // Desenha bolas ativas
    for (int i = 0; i < MAX_BALLS; ++i)
    {
        if (balls[i].active)
        {
            int ball_draw_x = (int)balls[i].x - BALL_RADIUS;
            int ball_draw_y = (int)balls[i].y - BALL_RADIUS;
            int ball_size = BALL_RADIUS * 2 + 1;

            // Garante que as coordenadas estejam dentro dos limites da tela
            if (ball_draw_x < 0)
                ball_draw_x = 0;
            if (ball_draw_y < 0)
                ball_draw_y = 0;
            if (ball_draw_x + ball_size > SSD1306_WIDTH)
                ball_draw_x = SSD1306_WIDTH - ball_size;
            if (ball_draw_y + ball_size > SSD1306_HEIGHT)
                ball_draw_y = SSD1306_HEIGHT - ball_size;

            ssd1306_draw_square(&display, ball_draw_x, ball_draw_y, ball_size, ball_size);
        }
    }

    // Desenha a contagem total de bolas
    char count_str[20];
    sprintf(count_str, "N:%lu", total_balls_dropped);
    ssd1306_draw_string(&display, 1, 1, 1, count_str); // Escala = 1

    // Desenha o indicador de desvio
    int bias_bar_center_x = SSD1306_WIDTH - 15;
    int bias_bar_y = 5;
    int bias_bar_width = 10; // Largura total do intervalo do indicador
    // Linha representando o intervalo
    ssd1306_draw_line(&display, bias_bar_center_x - bias_bar_width, bias_bar_y, bias_bar_center_x + bias_bar_width, bias_bar_y);
    // Posição do indicador com base no desvio
    int bias_indicator_x = bias_bar_center_x + (int)(bias * bias_bar_width);
    // Desenhe uma pequena linha vertical para o indicador
    ssd1306_draw_line(&display, bias_indicator_x, bias_bar_y - 2, bias_indicator_x, bias_bar_y + 2);
}

// Desenha a tela do histograma
void display_draw_histogram()
{
    display_clear();

    // Define a contagem máxima de canaletas para dimensionamento
    uint16_t max_count = 0;
    for (int i = 0; i < NUM_BINS; ++i)
    {
        if (bins[i] > max_count)
        {
            max_count = bins[i];
        }
    }

    // Desenha as barras do histograma
    for (int i = 0; i < NUM_BINS; ++i)
    {
        int bar_height = 0;
        if (max_count > 0)
        {
            // Altura em escala em relação à contagem máxima e ao espaço disponível
            bar_height = (int)(((float)bins[i] / max_count) * MAX_HISTO_HEIGHT);
        }
        if (bar_height < 0)
            bar_height = 0; // Garante que não seja negativo
        if (bar_height > MAX_HISTO_HEIGHT)
            bar_height = MAX_HISTO_HEIGHT; // Altura máxima

        int x_start = (int)(i * BIN_WIDTH);
        int bar_width = (int)BIN_WIDTH - 1; // Deixe um espaço de 1px
        if (bar_width < 1)
            bar_width = 1;

        // Garante que a barra não saia da tela
        if (x_start + bar_width >= SSD1306_WIDTH)
        {
            bar_width = SSD1306_WIDTH - x_start - 1;
        }
        if (x_start >= SSD1306_WIDTH)
            continue; // Pular se começar fora da tela

        int y_start = SSD1306_HEIGHT - 1 - bar_height; // Topo Y da barra
        // O cálculo de Y deve ser relativo ao fundo
        if (y_start < 10)
            y_start = 10; // Evita sobreposição de texto de título

        // Usa ssd1306_draw_square para desenhar retângulos preenchidos
        if (bar_height > 0 && bar_width > 0)
        { // Desenha somente se estiver visível
            ssd1306_draw_square(&display, x_start, y_start, bar_width, bar_height);
        }
    }

    // Contagem total de bolas e título
    char title_str[25];
    sprintf(title_str, "Histograma (N:%lu)", total_balls_dropped);
    ssd1306_draw_string(&display, 1, 1, 1, title_str); // Escala = 1
}
