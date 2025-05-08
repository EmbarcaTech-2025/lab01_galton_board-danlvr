# Projetos de Sistemas Embarcados - EmbarcaTech 2025

Autor: Danilo Oliveira Gonçalves

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, Maio de 2025

---

# Simulador de Galton Board

## 🎯 Objetivo do Projeto

Este projeto implementa um simulador interativo da Galton Board utilizando o microcontrolador RP2040 presente da placa de desenvolvimento BitDogLab. O objetivo é demonstrar visualmente a formação da distribuição normal à medida que bolas virtuais caem através de uma grade de pinos e se acumulam em compartimentos na base. O usuário pode influenciar a trajetória das bolas através de um joystick (controlando o "bias") e alternar entre a visualização da simulação em tempo real e um histograma da distribuição das bolas.

## 🔧 Componentes Utilizados

- Placa com microcontrolador RP2040 - BitDogLab
- Display OLED SSD1306 (128x64 pixels, interface I2C)
- Joystick analógico (para controle de bias)
- Botões de pressão (para adicionar bolas e alternar visualização)

## 📌 Pinagem do Dispositivo

Abaixo estão os nomes das constantes usadas no projeto e a pinagem exata das definições em `config.h`. :

| Constante           | Pino RP2040     | Função          | Conexão                |
|---------------------------------------|-----------------|------------------------|
| `I2C_SDA_PIN`       |       14        | SDA (I2C0)      | Display OLED SSD1306   |
| `I2C_SCL_PIN`       |       15        | SCL (I2C0)      | Display OLED SSD1306   |
| `JOYSTICK_X_GPIO`   |       27        | ADC (Eixo X)    | Joystick               |
| `BUTTON_A_PIN`      |        5        | Entrada Digital | Botão Adicionar Bola   |
| `BUTTON_B_PIN`      |        6        | Entrada Digital | Botão Alternar Visão   |

## 📸 Demonstração do funcionamento

![Demonstração da Tábua de Galton](assets/galton_board_sim.gif)
(A demonstração visual do projeto seria inserida aqui, mostrando as bolas caindo e o histograma se formando.)

## 📊 Resultados Esperados/Observados

- Ao iniciar, o display OLED exibe uma mensagem de carregamento e, em seguida, a visualização da simulação da Galton Board.
- Bolas virtuais caem do topo, colidindo com os pinos e desviando probabilisticamente para a esquerda ou direita.
- O joystick permite ao usuário introduzir um "bias" (tendência), influenciando a probabilidade de desvio das bolas e, consequentemente, deslocando o pico da distribuição resultante.
- As bolas se acumulam nos compartimentos (bins) na base do display.
- Pressionar o botão "Adicionar Bola" (`BUTTON_PIN_ADD_BALL`) introduz uma nova bola na simulação a partir do topo.
- Pressionar o botão "Alternar Visão" (`BUTTON_PIN_TOGGLE_VIEW`) alterna a exibição entre a simulação em tempo real das bolas caindo (`VIEW_SIMULATION`) e um histograma (`VIEW_HISTOGRAM`) que mostra a contagem de bolas em cada compartimento.
- O histograma, com um número suficiente de bolas, deve visualmente aproximar-se de uma curva de distribuição normal. O bias aplicado pelo joystick deve deslocar o centro desta curva.
- O display exibe continuamente a contagem total de bolas que já caíram (`N:`) e um indicador visual do bias aplicado pelo joystick.

## 🔍 Notas Técnicas

- A simulação modela a queda das bolas e as colisões com os pinos. A direção após uma colisão com um pino é determinada probabilisticamente, e o valor lido do joystick (bias) ajusta essa probabilidade.
- O estado da simulação, incluindo a posição de cada bola ativa e a contagem de bolas em cada compartimento, é atualizado em loop contínuo.
- O display OLED SSD1306 é controlado via interface I2C, utilizando o driver `ssd1306` para renderizar os elementos gráficos (pinos, bolas, histograma, texto).
- O joystick analógico é lido através de um canal ADC (Analog-to-Digital Converter) para determinar o nível de bias.
- Os botões são configurados como entradas digitais e utilizam interrupções de hardware (IRQ) para detectar pressionamentos de forma eficiente.
- O projeto é estruturado com uma camada de abstração de hardware (HAL), drivers de periféricos e a lógica da aplicação.
- Duas visualizações principais são gerenciadas: `VIEW_SIMULATION` para a animação dinâmica das bolas e `VIEW_HISTOGRAM` para a representação estática da distribuição acumulada.

## 📚 Bibliotecas Utilizadas

- Raspberry Pi Pico SDK (`pico-sdk`): SDK oficial para desenvolvimento no RP2040.
- [pico-ssd1306](https://github.com/daschr/pico-ssd1306) - Biblioteca para utilização de displays SSD1306 com o Raspberry Pi Pico e o pico-sdk.

---

## 📜 Licença
MIT License - MIT GPL-3.0.

