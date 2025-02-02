#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/gpio.h"
#include "ws2818b.pio.h"
//Definição da quantidade de LEDs e frames da animação
#define LED_COUNT 25
#define FRAMES_ANIMATION 10

// Definição dos pinos dos botões e LED RGB
#define BUTTON_A 5
#define BUTTON_B 6
#define LED_RED 13
#define LED_GREEN 11
#define LED_BLUE 12
#define MATRIX_PIN 7

// Definição do debounce time dos botões
#define BUTTON_DEBOUNCE_TIME 700

// Definição de pixel GRB
struct pixel_t {
    uint8_t G, R, B; // Ordem GRB para compatibilidade com WS2812B
};
typedef struct pixel_t pixel_t;

// Declaração do buffer de pixels que formam a matriz.
pixel_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

// Variáveis globais para controle do número exibido e estado dos botões
volatile uint8_t number = 0;
volatile bool pressed_a_button = false;
volatile bool pressed_b_button = false;
volatile uint32_t last_time_pressed_a = 0;
volatile uint32_t last_time_pressed_b = 0;

//Inicializa a máquina PIO para controle da matriz de LEDs.
void npInit(uint pin) {
    // Cria programa PIO.
    uint offset = pio_add_program(pio0, &ws2818b_program);
    np_pio = pio0;

    // Toma posse de uma máquina PIO.
    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0) {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true);
    }

    // Inicia programa na máquina PIO obtida.
    ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

    // Limpa buffer de pixels.
    for (uint i = 0; i < LED_COUNT; ++i) {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

//Atribui uma cor RGB a um LED.
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
    leds[index].R = r;
    leds[index].G = g;
    leds[index].B = b;
}

//Limpa o buffer de pixels
void npClear() {
    for (uint i = 0; i < LED_COUNT; ++i)
        npSetLED(i, 0, 0, 0);
}

//Escreve os dados do buffer nos LEDs.
void npWrite() {
    for (uint i = 0; i < LED_COUNT; ++i) {
        pio_sm_put_blocking(np_pio, sm, leds[i].G);
        pio_sm_put_blocking(np_pio, sm, leds[i].R);
        pio_sm_put_blocking(np_pio, sm, leds[i].B);
    }
    sleep_us(100); // Espera 100us, sinal de RESET
}

//Função para calcular o índice do LED na matriz.
int getIndex(int x, int y) {
    if (y % 2 == 0) {
        return 24 - (y * 5 + x);
    } else {
        return 24 - (y * 5 + (4 - x));
    }
}

//Função para exibir um número na matriz de LEDs.
void display(uint8_t num) {
    // Definição das matrizes para os números (0-9)
    const int numbers[FRAMES_ANIMATION][5][5][3] = {
        // Número 0
    {
            {{0, 0, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {0, 0, 0}},
            {{255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0}},
            {{255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0}},
            {{255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0}},
            {{0, 0, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {0, 0, 0}}
        },

        {
            {{0, 0, 0}, {0, 0, 0}, {230, 245, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {230, 245, 0}, {230, 245, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {230, 245, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {0, 0, 0}, {230, 245, 0}, {0, 0, 0}, {0, 0, 0}},
            {{0, 0, 0}, {230, 245, 0}, {230, 245, 0}, {230, 245, 0}, {0, 0, 0}}
        },

        {
            {{0, 0, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {204, 235, 0}},
            {{204, 235, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}},
            {{204, 235, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{204, 235, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}}
        },

        {
            {{179, 224, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {179, 224, 0}},
            {{0, 0, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {179, 224, 0}},
            {{179, 224, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}}
        },

        {
            {{153, 214, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {153, 214, 0}},
            {{153, 214, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {153, 214, 0}},
            {{153, 214, 0}, {153, 214, 0}, {153, 214, 0}, {153, 214, 0}, {153, 214, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {153, 214, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {153, 214, 0}}
        },

        {
            {{128, 204, 0}, {128, 204, 0}, {128, 204, 0}, {128, 204, 0}, {0, 0, 0}},
            {{128, 204, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{128, 204, 0}, {128, 204, 0}, {128, 204, 0}, {128, 204, 0}, {128, 204, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {128, 204, 0}},
            {{0, 0, 0}, {128, 204, 0}, {128, 204, 0}, {128, 204, 0}, {128, 204, 0}}
        },

        {
            {{102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {0, 0, 0}},
            {{102, 194, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            {{102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {102, 194, 0}},
            {{102, 194, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {102, 194, 0}},
            {{102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {102, 194, 0}}
        },

        {
            {{76, 184, 0}, {76, 184, 0}, {76, 184, 0}, {76, 184, 0}, {76, 184, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {76, 184, 0}},
            {{0, 0, 0}, {0, 0, 0}, {76, 184, 0}, {76, 184, 0}, {76, 184, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {76, 184, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {76, 184, 0}}
        },

        {
            {{51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}},
            {{51, 173, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {51, 173, 0}},
            {{51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}},
            {{51, 173, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {51, 173, 0}},
            {{51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}}
        },

        {
            {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
            {{0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}},
            {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}},
            {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}}
        }
    };

    npClear();

    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            int posicao = getIndex(x, y);
            npSetLED(posicao, numbers[num][y][x][0], numbers[num][y][x][1], numbers[num][y][x][2]);
        }
    }

    npWrite();
}

//Callback para interrupções dos botões.
void gpio_callback(uint gpio, uint32_t events) {
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (gpio == BUTTON_A) {
        if (current_time - last_time_pressed_a > BUTTON_DEBOUNCE_TIME) {
            pressed_a_button = true;
            last_time_pressed_a = current_time;
        }
    } else if (gpio == BUTTON_B) {
        if (current_time - last_time_pressed_b > BUTTON_DEBOUNCE_TIME) {
            pressed_b_button = true;
            last_time_pressed_b = current_time;
        }
    }
}

int main() {
    // Inicializa entradas e saídas.
    stdio_init_all();

    // Inicializa matriz de LEDs NeoPixel.
    npInit(MATRIX_PIN);
    npClear();

    // Inicializa os pinos do LED RGB
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);

    // Inicializa os botões com resistores de pull-up internos
    gpio_init(BUTTON_A);
    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_A);
    gpio_pull_up(BUTTON_B);

    // Configura interrupções para os botões
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    // Exibe o número inicial (0)
    display(number);

    // Loop principal com animação automática
    while (true) {
        gpio_put(LED_RED, 1);
        sleep_ms(100);
        gpio_put(LED_RED, 0);
        sleep_ms(100);

        // Controle manual pelos botões
        if (pressed_a_button) {
            pressed_a_button = false;
            number = (number < 9) ? number + 1 : 0;
            display(number);
        }

        if (pressed_b_button) {
            pressed_b_button = false;
            number = (number > 0) ? number - 1 : 9;
            display(number);
        }

        
    }
}