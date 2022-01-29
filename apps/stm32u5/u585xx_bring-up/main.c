#include <stdlib.h>
#include <string.h>

#include "bsp.h"
#include "delay.h"
#include "gpio.h"
#include "logger.h"

int main() {
    Assert(bsp_init(), 0);

    while (1) {
        LOG_INFO("Test!\n");
        bool r_value = !hal_gpio_read(BSP_USER_BUTTON_PORT, BSP_USER_BUTTON_PIN);
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, false);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, r_value);
        delay_ms(500);
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, true);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, r_value);
        delay_ms(300);
        __asm("LDR  r0, = 0xAAAAAAAA");
        __asm("NOP");
    }
}
