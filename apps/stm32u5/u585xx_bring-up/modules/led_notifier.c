#include "modules.h"
#include "hal_gpio.h"
#include "delay.h"
#include "bsp.h"

void idle_notifier(void) {
    hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, false);
    delay_ms(500);
    hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, true);
    delay_ms(300);
}

void error_blink() {
    hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, false);
    delay_ms(500);
    hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, true);
}
