#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp.h"
#include "gpio.h"

int main() {
    hal_gpio_open(BSP_GREEN_LED_PORT);
    hal_gpio_open(BSP_RED_LED_PORT);
    hal_gpio_open(BSP_USER_BUTTON_PORT);
    hal_gpio_ioctl(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, gpio_ioctl_output);
    hal_gpio_ioctl(BSP_RED_LED_PORT, BSP_RED_LED_PIN, gpio_ioctl_output);
    hal_gpio_ioctl(BSP_USER_BUTTON_PORT, BSP_USER_BUTTON_PIN, gpio_ioctl_digital_input);

    while (1) {
        bool r_value = hal_gpio_read(BSP_USER_BUTTON_PORT, BSP_USER_BUTTON_PIN);
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, true);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, r_value);
        for (int i = 0; i < 100000; i++) {
            __asm("NOP");
        }
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, false);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, r_value);
        for (int i = 0; i < 100000; i++) {
            __asm("NOP");
        }
        __asm("LDR  r0, = 0xAAAAAAAA");
        __asm("NOP");
    }
}
