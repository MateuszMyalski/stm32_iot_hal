#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bsp.h"
#include "gpio.h"
#include "logger.h"

#ifdef USE_SEMIHOSTING
extern void initialise_monitor_handles(void);
#endif  // USE_SEMIHOSTING

int main() {
    setvbuf(stdout, NULL, _IONBF, 0); // turn off buffering for stdout
    char static_array[200];
    setvbuf(stdout, static_array, _IOLBF, sizeof(static_array));
    Assert(bsp_init_led(), 0);
#ifdef USE_SEMIHOSTING
    initialise_monitor_handles();
    printf("Semihosting turned on!\n");
#endif  // USE_SEMIHOSTING
    int tmp = 2;
    char str[] = "AAAAA";
    while (1) {
        int a = printf("No end");
        int b = printf("Hello Wrold222!\r\n");
        int c = printf("str: %s\r\n", str);
        int d = printf("value%d!\r\n", 2);
        LOG_WARN("Warning\r\n");
        LOG_ERR("ERr\r\n");
        LOG_SUCCESS("Success\r\n");
        LOG_WARN("Warning with value %d\r\n", tmp);
        bool r_value = !hal_gpio_read(BSP_USER_BUTTON_PORT, BSP_USER_BUTTON_PIN);
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, false);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, r_value);
        for (int i = 0; i < 100000; i++) {
            __asm("NOP");
        }
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, true);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, r_value);
        for (int i = 0; i < 100000; i++) {
            __asm("NOP");
        }
        __asm("LDR  r0, = 0xAAAAAAAA");
        __asm("NOP");
    }
}
