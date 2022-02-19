#include "bsp.h"
#include "delay.h"
#include "hal_gpio.h"
#include "modules.h"

#define ERROR_BLINKS 3L

void idle_notifier(void) {
    bool prev_led_status = hal_gpio_read(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN);

    hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, !prev_led_status);
    delay_ms(300);
    hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, !prev_led_status);
    delay_ms(300);
}

void error_blink() {
    bool prev_led_status = hal_gpio_read(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN);

    for (int i = 0; i < ERROR_BLINKS; i++) {
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, !prev_led_status);
        delay_ms(300);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, !prev_led_status);
        delay_ms(300);
    }
}
