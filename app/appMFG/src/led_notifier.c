#include "led_notifier.h"

#include "bsp.h"
#include "delay.h"
#include "hal_gpio.h"

#define ERROR_BLINKS 3L
#define HAPPY_BLINKS 12L

void led_notifier_idle(void) {
    bool prev_led_status = hal_gpio_read(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN);

    hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, !prev_led_status);
    delay_ms(300);
    hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, !prev_led_status);
    delay_ms(300);
}

void led_notifier_error_blink() {
    bool prev_led_status = hal_gpio_read(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN);

    for (int i = 0; i < ERROR_BLINKS; i++) {
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, !prev_led_status);
        delay_ms(300);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, !prev_led_status);
        delay_ms(300);
    }
}

void led_notifier_happy_blink() {
    bool init_red_led_status   = hal_gpio_read(BSP_RED_LED_PORT, BSP_RED_LED_PIN);
    bool init_green_led_status = hal_gpio_read(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN);

    for (int i = 0; i < HAPPY_BLINKS; i++) {
        bool prev_red_led_status   = hal_gpio_read(BSP_RED_LED_PORT, BSP_RED_LED_PIN);
        bool prev_green_led_status = hal_gpio_read(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN);

        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, !prev_red_led_status);
        delay_ms(100);
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, !prev_green_led_status);
        delay_ms(100);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, !prev_red_led_status);
        delay_ms(100);
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, !prev_green_led_status);
        delay_ms(100);
    }

    hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, init_red_led_status);
    hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, init_green_led_status);
}
