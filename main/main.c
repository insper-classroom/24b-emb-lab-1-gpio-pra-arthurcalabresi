/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

const int BTN_PIN = 15;
const int LED_PIN = 16;
const int MOTOR_PIN_1 = 13;
const int MOTOR_PIN_2 = 12;
const int MOTOR_PIN_3 = 11;
const int MOTOR_PIN_4 = 10;

int main() {
    stdio_init_all();

    // Inicializando o botao
    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_up(BTN_PIN);

    // Inicializando o led
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Inicializando o motor
    gpio_init(MOTOR_PIN_1);
    gpio_set_dir(MOTOR_PIN_1, GPIO_OUT);
    gpio_init(MOTOR_PIN_2);
    gpio_set_dir(MOTOR_PIN_2, GPIO_OUT);
    gpio_init(MOTOR_PIN_3);
    gpio_set_dir(MOTOR_PIN_3, GPIO_OUT);
    gpio_init(MOTOR_PIN_4);
    gpio_set_dir(MOTOR_PIN_4, GPIO_OUT);


    while (true) {
        if (!gpio_get(BTN_PIN)) {
            gpio_put(LED_PIN, 1);
            printf("Botao pressionado\n");

            int pisca_led = 0;

            for (int i = 0; i < 2048/4; i++) {
                gpio_put(MOTOR_PIN_1, 1);
                gpio_put(MOTOR_PIN_2, 0);
                gpio_put(MOTOR_PIN_3, 0);
                gpio_put(MOTOR_PIN_4, 0);
                sleep_ms(10);
                gpio_put(MOTOR_PIN_1, 0);
                gpio_put(MOTOR_PIN_2, 1);
                gpio_put(MOTOR_PIN_3, 0);
                gpio_put(MOTOR_PIN_4, 0);
                sleep_ms(10);
                gpio_put(MOTOR_PIN_1, 0);
                gpio_put(MOTOR_PIN_2, 0);
                gpio_put(MOTOR_PIN_3, 1);
                gpio_put(MOTOR_PIN_4, 0);
                sleep_ms(10);
                gpio_put(MOTOR_PIN_1, 0);
                gpio_put(MOTOR_PIN_2, 0);
                gpio_put(MOTOR_PIN_3, 0);
                gpio_put(MOTOR_PIN_4, 1);
                sleep_ms(10);
                pisca_led += 1;
                if (pisca_led > 10)
                {
                    gpio_put(LED_PIN, !gpio_get(LED_PIN));
                    pisca_led = 0;
                }
                
            }
            gpio_put(LED_PIN, 0);
        }
        
    }
}
