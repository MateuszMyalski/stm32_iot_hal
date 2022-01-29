#include <stdint.h>

#define LL_CANARY_REGISTER_SET(x) \
    do {                          \
        __asm("LDR  r0, = " #x);  \
    } while (0);

extern volatile uint32_t SysTick_msTicks = 0; /* Variable to store millisecond ticks */

void BusFault_Handler(void) {
    while (1) {
        LL_CANARY_REGISTER_SET(0xAAAABBBB);
        // Hang the device
    }
}

void HardFault_Handler(void) {
    while (1) {
        LL_CANARY_REGISTER_SET(0xBBBBAAAA);
        // Hang the device
    }
}

void SysTick_Handler(void) { SysTick_msTicks++; }
