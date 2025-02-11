#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22 // Pino do servo motor
#define PWM_WRAP 20000  // Período de 20ms (50Hz)

// Definição dos pulsos para os ângulos
#define SERVO_0   500   // 0° (500µs)
#define SERVO_90  1470  // 90° (1470µs)
#define SERVO_180 2400  // 180° (2400µs)

#define SMOOTH_STEP 5   // Passo de incremento (5µs)
#define SMOOTH_DELAY 10 // Tempo entre cada ajuste (10ms)

#define WAIT_TIME_MS 5000 // Tempo de espera entre posições fixas (5s)

// Configura o PWM
void setup_pwm(uint gpio) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(gpio);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, 125.0f); // Ajusta frequência para ~50Hz
    pwm_config_set_wrap(&config, PWM_WRAP);
    pwm_init(slice, &config, true);
}

// Define o ciclo ativo do PWM
void set_servo_position(uint gpio, uint pulse) {
    pwm_set_gpio_level(gpio, pulse);
}

int main() {
    stdio_init_all();
    setup_pwm(SERVO_PIN);

    // Posicionamento inicial fixo
    set_servo_position(SERVO_PIN, SERVO_180); // 180°
    sleep_ms(WAIT_TIME_MS);

    set_servo_position(SERVO_PIN, SERVO_90); // 90°
    sleep_ms(WAIT_TIME_MS);

    set_servo_position(SERVO_PIN, SERVO_0); // 0°
    sleep_ms(WAIT_TIME_MS);

    // Movimento contínuo suave entre 0° e 180° e de volta
    while (1) {
        // Movimento suave de 0° a 180°
        for (uint pulse = SERVO_0; pulse <= SERVO_180; pulse += SMOOTH_STEP) {
            set_servo_position(SERVO_PIN, pulse);
            sleep_ms(SMOOTH_DELAY);
        }

        // Movimento suave de 180° a 0°
        for (uint pulse = SERVO_180; pulse >= SERVO_0; pulse -= SMOOTH_STEP) {
            set_servo_position(SERVO_PIN, pulse);
            sleep_ms(SMOOTH_DELAY);
        }
    }

    return 0;
}
