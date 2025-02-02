#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

//Definição dos pinos dos leds
#define LED_RED 11     
#define LED_YELLOW 12  
#define LED_GREEN 13   

//Vetor com a sequência correta dos leds
const uint8_t pins[] = {LED_RED, LED_YELLOW, LED_GREEN}; 

// Contador para controlar os estados dos leds
uint8_t color = 1; 

//Matrz que define os estados dos leds
int led_colors[3][3] = {
    {1, 0, 0},
    {0, 1, 0},
    {0, 0, 1}
};

//Função para inicializar os leds (O led vermelho já inicia ligado)
void init_all_leds()
{
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_put(LED_RED, true);

    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
}

//Liga os leds de acordo com a sequência definida pela variavel 'color'
void turn_on_leds()
{
    for (int i = 0; i < 3; i++)
        gpio_put(pins[i], led_colors[color][i]);
}

//Função de callback acionada pelo temporizador
bool repeating_timer_callback(struct repeating_timer *t)
{
    turn_on_leds();
    printf("\nPassaram 3 segundos!\n");

    //Incrementa o valor do contador
    color = ++color > 2 ? 0 : color; 
    return true;
}

int main()
{
    stdio_init_all();
    init_all_leds();

    struct repeating_timer timer;

    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        printf("Semafóro em funcionamento...\n");
        sleep_ms(1000);
    }
}