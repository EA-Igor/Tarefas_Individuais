#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs e botão
#define LED_GREEN 11    // LED Azul
#define LED_BLUE 12     // LED Vermelho
#define LED_RED 13   // LED Verde
#define BUTTON 5       // Botão A

// Vetor com a sequência correta dos LEDs
const uint8_t leds[] = {LED_GREEN, LED_BLUE, LED_RED};

// Contador para controlar os estados dos LEDs
uint8_t state = 0;

// Matriz que define os estados dos LEDs
int led_states[4][3] = {
    {1, 1, 1},  // Todos ligados
    {0, 1, 1},  // Azul desligado
    {0, 0, 1},  // Azul e Vermelho desligados
    {0, 0, 0}   // Todos desligados
};

volatile bool button_pressed = false;
volatile bool timer_running = false;

// Inicializa os LEDs e o botão
void init_peripherals()
{
    for (int i = 0; i < 3; i++) {
        gpio_init(leds[i]);
        gpio_set_dir(leds[i], GPIO_OUT);
    }
    
    gpio_init(BUTTON);
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);
}

// Atualiza os LEDs de acordo com o estado atual
void update_leds()
{
    for (int i = 0; i < 3; i++) {
        gpio_put(leds[i], led_states[state][i]);
    }
}

// Callback do temporizador
bool timer_callback(struct repeating_timer *t)
{
    state++;
    if (state > 3) {
        timer_running = false;
        return false; // Para o temporizador
    }
    update_leds();
    return true;
}

// Callback do botão
void button_callback(uint gpio, uint32_t events)
{
    if (gpio == BUTTON && !timer_running) {
        button_pressed = true;
    }
}

int main()
{
    stdio_init_all();
    init_peripherals();
    gpio_set_irq_enabled_with_callback(BUTTON, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    struct repeating_timer timer;

    while (true) {
        if (button_pressed && !timer_running) {
            button_pressed = false;
            timer_running = true;
            state = 0;
            update_leds();
            add_repeating_timer_ms(3000, timer_callback, NULL, &timer);
        }
        sleep_ms(100);
    }
}
