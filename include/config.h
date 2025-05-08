#ifndef CONFIG_H
#define CONFIG_H

// Dimensões do display
#define SSD1306_WIDTH 128 // Largura do display
#define SSD1306_HEIGHT 64 // Altura do display

// Definições de pinos
#define BUTTON_A_PIN 5           // GPIO5 Botão A (Adicionar Bola)
#define BUTTON_B_PIN 6           // GPIO6 Botão B (Alternar Visualização)
#define I2C_SDA_PIN 14           // GPIO14 SDA
#define I2C_SCL_PIN 15           // GPIO15 SCL
#define I2C_PORT i2c1            // Porta I2C 1
#define JOYSTICK_X_GPIO 27       // VRx no GPIO27 -> ADC1
#define JOYSTICK_X_ADC_CHANNEL 1 // Canal ADC para GPIO27

// Calibração do joystick
#define RAW_X_MIN 12
#define RAW_X_MAX 4076
#define JOYSTICK_DEADZONE 200 // Ignora pequenos movimentos em torno do centro

// Parâmetros da simulação
#define MAX_BALLS 50                // Número máximo de bolas simultâneas na tela
#define NUM_PIN_ROWS 9              // Número de linhas de pinos
#define PINS_PER_ROW(row) (row + 1) // Pinos numa coluna específica (base 0)
#define PIN_ROW_START_Y 10          // Coordenada Y do topo da primeira linha de pinos
#define PIN_ROW_SPACING 5           // Distância vertical entre linhas de pinos
#define PIN_HORIZONTAL_SPACING 8    // Espaço horizontal aproximado entre os pinos
#define BALL_RADIUS 1
#define BOTTOM_Y (PIN_ROW_START_Y + (NUM_PIN_ROWS * PIN_ROW_SPACING) + 5) // Nível Y onde as canaletas começam

#define NUM_BINS 16                                 // Número de canaletas
#define BIN_WIDTH ((float)SSD1306_WIDTH / NUM_BINS) // Largura de cada canaleta
#define MAX_HISTO_HEIGHT (SSD1306_HEIGHT - 15)      // Altura máxima da barra do histograma

// Configurações de tempo
#define LOOP_DELAY_MS 30      // Atraso para controle de velocidade de simulação
#define DEBOUNCE_DELAY_MS 150 // Atraso para debounce de botão

#endif // CONFIG_H
