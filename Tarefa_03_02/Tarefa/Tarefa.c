// Inclusão de bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"     // SDK do Raspberry Pi Pico
#include "hardware/pio.h"    // Programmable I/O (PIO)
#include "hardware/i2c.h"    // Hardware I2C
#include "hardware/clocks.h" // Controle de clock
#include "lib/font.h"        // Fontes para o display
#include "lib/ssd1306.h"     // Driver do display
#include "ws2812b.pio.h"     // Arquivo gerado pelo PIO assembler

// Definição da quantidade de LEDs
#define LED_COUNT 25 // Número de LEDs na matriz
#define BRIGHTNESS 0.1 // Brilho dos LEDs

// Definição dos pinos dos botões e LED RGB
#define BUTTON_A 5   // Botão A
#define BUTTON_B 6   // Botão B
#define MATRIX_PIN 7 // Pino da matriz de LEDs
#define LED_GREEN 11 // LED Verde
#define LED_BLUE 12  // LED Azul
#define LED_RED 13   // LED Vermelho

// Definição dos pinos e portas do display OLED SSD1306
#define I2C_PORT i2c1 // Porta I2C utilizada
#define I2C_SDA 14    // Pino SDA
#define I2C_SCL 15    // Pino SCL
#define address 0x3C // Endereço I2C do display

// Definição do debounce time dos botões
#define BUTTON_DEBOUNCE_TIME 700

// Variáveis globais para controle do número exibido e estado dos botões
volatile bool pressed_a_button = false; // Variável para indicar que o botão A foi pressionado
volatile bool pressed_b_button = false; // Variável para indicar que o botão B foi pressionado
volatile uint32_t last_time_pressed_a = 0; // Variável da última vez que o botão A foi pressionado
volatile uint32_t last_time_pressed_b = 0; // Variável da última vez que o botão B foi pressionado

// Variáveis para uso da máquina PIO.
static PIO np_pio; // Instância do PIO
static uint sm;    // State Machine do PIO
ssd1306_t ssd;     // Estrutura do display
bool cor = true;   // Cor de fundo do display

// Definição de pixel GRB
struct pixel_t
{
    uint8_t G, R, B; // Ordem GRB para compatibilidade com WS2812B
};

typedef struct pixel_t pixel_t;

// Declaração do buffer de pixels que formam a matriz.
pixel_t leds[LED_COUNT];

// Inicializa a máquina PIO para controle da matriz de LEDs.
void npInit(uint pin)
{
    // Cria programa PIO.
    uint offset = pio_add_program(pio0, &ws2812b_program);
    np_pio = pio0;

    // Toma posse de uma máquina PIO.
    sm = pio_claim_unused_sm(np_pio, false);
    if (sm < 0)
    {
        np_pio = pio1;
        sm = pio_claim_unused_sm(np_pio, true);
    }

    // Inicia programa na máquina PIO obtida.
    ws2812b_program_init(np_pio, sm, offset, pin, 800000.f);

    // Limpa buffer de pixels.
    for (uint i = 0; i < LED_COUNT; ++i)
    {
        leds[i].R = 0;
        leds[i].G = 0;
        leds[i].B = 0;
    }
}

// Atribui uma cor RGB a um LED.
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b)
{
    leds[index].R = r * BRIGHTNESS;
    leds[index].G = g * BRIGHTNESS;
    leds[index].B = b * BRIGHTNESS;
}

// Limpa o buffer de pixels
void npClear()
{
    for (uint i = 0; i < LED_COUNT; ++i)
        npSetLED(i, 0, 0, 0);
}

// Função para calcular o índice do LED na matriz.
int getIndex(int x, int y)
{
    if (y % 2 == 0)
    {
        return 24 - (y * 5 + x);
    }
    else
    {
        return 24 - (y * 5 + (4 - x));
    }
}

// Função para enviar dados para os LEDs
void send_to_leds() {
    for (uint i = 0; i < LED_COUNT; ++i) {
        uint32_t pixel_color = ((uint32_t)leds[i].G << 16) | ((uint32_t)leds[i].R << 8) | leds[i].B;
        pio_sm_put_blocking(np_pio, sm, pixel_color);
    }
}

void matrix(uint8_t num)
{
    // Definição das matrizes para os números (0-9)
    const int numbers[11][5][5][3] = {
        // Número 0
        {{{0, 0, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {0, 0, 0}},
         {{255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0}},
         {{255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0}},
         {{255, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {255, 255, 0}},
         {{0, 0, 0}, {255, 255, 0}, {255, 255, 0}, {255, 255, 0}, {0, 0, 0}}},

        // Número 1
        {{{0, 0, 0}, {0, 0, 0}, {230, 245, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {230, 245, 0}, {230, 245, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {230, 245, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {230, 245, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {230, 245, 0}, {230, 245, 0}, {230, 245, 0}, {0, 0, 0}}},

        // Número 2
        {{{0, 0, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {204, 235, 0}},
         {{204, 235, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}},
         {{204, 235, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
         {{204, 235, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}, {204, 235, 0}}},

        // Número 3
        {{{179, 224, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {179, 224, 0}},
         {{0, 0, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {179, 224, 0}},
         {{179, 224, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}, {179, 224, 0}}},

        // Número 4
        {{{153, 214, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {153, 214, 0}},
         {{153, 214, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {153, 214, 0}},
         {{153, 214, 0}, {153, 214, 0}, {153, 214, 0}, {153, 214, 0}, {153, 214, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {153, 214, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {153, 214, 0}}},

        // Número 5
        {{{128, 204, 0}, {128, 204, 0}, {128, 204, 0}, {128, 204, 0}, {0, 0, 0}},
         {{128, 204, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
         {{128, 204, 0}, {128, 204, 0}, {128, 204, 0}, {128, 204, 0}, {128, 204, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {128, 204, 0}},
         {{0, 0, 0}, {128, 204, 0}, {128, 204, 0}, {128, 204, 0}, {128, 204, 0}}},

        // Número 6
        {{{102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {0, 0, 0}},
         {{102, 194, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
         {{102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {102, 194, 0}},
         {{102, 194, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {102, 194, 0}},
         {{102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {102, 194, 0}, {102, 194, 0}}},

        // Número 7
        {{{76, 184, 0}, {76, 184, 0}, {76, 184, 0}, {76, 184, 0}, {76, 184, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {76, 184, 0}},
         {{0, 0, 0}, {0, 0, 0}, {76, 184, 0}, {76, 184, 0}, {76, 184, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {76, 184, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {76, 184, 0}}},

        // Número 8
        {{{51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}},
         {{51, 173, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {51, 173, 0}},
         {{51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}},
         {{51, 173, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {51, 173, 0}},
         {{51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}, {51, 173, 0}}},

        // Número 9
        {{{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
         {{0, 255, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}},
         {{0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}, {0, 255, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 255, 0}}},

        {// 10 - Apaga o display
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
         {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}};

    npClear();

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            int posicao = getIndex(x, y);
            npSetLED(posicao, numbers[num][y][x][0], numbers[num][y][x][1], numbers[num][y][x][2]);
        }
    }
    send_to_leds();
}

// Callback para interrupções dos botões.
void gpio_callback(uint gpio, uint32_t events)
{
    uint32_t current_time = to_ms_since_boot(get_absolute_time());

    if (gpio == BUTTON_A)
    {
        if (current_time - last_time_pressed_a > BUTTON_DEBOUNCE_TIME)
        {
            pressed_a_button = true;
            last_time_pressed_a = current_time;
            gpio_put(LED_GREEN, !gpio_get(LED_GREEN)); // Inverte o estado do LED verde
            if (gpio_get(LED_GREEN) == 0)
            {
                printf("LED verde Desativado\n");
                ssd1306_fill(&ssd, !cor); // Limpa o display
                ssd1306_draw_string(&ssd, "Verde          suspenso", 30, 30); // Desenha uma string
                ssd1306_send_data(&ssd); // Atualiza o display
            }
            else
            {
                printf("LED verde Ativado\n");
                ssd1306_fill(&ssd, !cor); 
                ssd1306_draw_string(&ssd, "Verde ativo", 30, 30); 
                ssd1306_send_data(&ssd); 
            }
        }
    }
    else if (gpio == BUTTON_B)
    {
        if (current_time - last_time_pressed_b > BUTTON_DEBOUNCE_TIME)
        {
            pressed_b_button = true;
            last_time_pressed_b = current_time;
            gpio_put(LED_BLUE, !gpio_get(LED_BLUE)); // Inverte o estado do LED verde
            if (gpio_get(LED_BLUE) == 0)
            {
                printf("LED azul Desativado\n");
                ssd1306_fill(&ssd, !cor); 
                ssd1306_draw_string(&ssd, "Azul           suspenso", 30, 30); 
                ssd1306_send_data(&ssd); 
            }
            else
            {
                printf("LED azul Ativado\n");
                ssd1306_fill(&ssd, !cor); 
                ssd1306_draw_string(&ssd, "Azul ativo", 30, 30); 
                ssd1306_send_data(&ssd); 
            }
        }
    }
}

int main()
{
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

    // Inicializa a matriz de LEDs apagada
    matrix(10);

    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA); 
    gpio_pull_up(I2C_SCL);
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, address, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd);

    // Limpa o display
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);

    char c = 0;

    while (true)
    {
        
        printf("Digite um caractere e pressione Enter: \n"); // Solicita que o usuário informe um caractere
        fflush(stdout); // Garante que a mensagem seja exibida imediatamente

        // Aguarda a entrada de um caractere
        char c = 0;
        while (true)
        {
            int input = getchar_timeout_us(100000); // Aguarda 100ms por uma entrada
            if (input != PICO_ERROR_TIMEOUT)
            {
                c = (char)input;
                break;
            }
            tight_loop_contents(); // Evita que o processador entre em modo de espera
        }

        if (c == '0' || c == '1' || c == '2' || c == '3' || c == '4' || c == '5' || c == '6' || c == '7' || c == '8' || c == '9')
        {
            matrix(c - '0');
        }
        else
        {
            matrix(10);
        }

        ssd1306_fill(&ssd, !cor); // Limpa o display
        ssd1306_draw_char(&ssd, c, 60, 30); // Desenha o caractere no display
        ssd1306_send_data(&ssd); // Atualiza o display
    }
    return 0;
}