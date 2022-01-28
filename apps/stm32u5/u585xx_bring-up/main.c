#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stm32u585xx.h"
#include "gpio.h"

int main() {
    hal_gpio_open(GPIOH);
    hal_gpio_ioctl(GPIOH, 6, gpio_ioctl_output);
    hal_gpio_ioctl(GPIOH, 7, gpio_ioctl_output);

    

    while (1) {
        hal_gpio_write(GPIOH, 6, 1);
        hal_gpio_write(GPIOH, 7, 0);
        for(int i = 0; i < 100000; i++){
            __asm("NOP");
        }
        hal_gpio_write(GPIOH, 6, 0);
        hal_gpio_write(GPIOH, 7, 1);
        for(int i = 0; i < 100000; i++){
            __asm("NOP");
        }
        __asm("LDR  r0, = 0xAAAAAAAA");
        __asm("NOP");
    }
}
