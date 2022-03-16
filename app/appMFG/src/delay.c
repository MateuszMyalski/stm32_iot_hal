#include "delay.h"

extern volatile uint32_t SysTick_msTicks;

void delay_ms(uint32_t delay) {
    uint32_t start_SysTick = SysTick_msTicks;
    uint64_t _end_SysTick  = start_SysTick + delay;
    uint32_t end_SysTick   = _end_SysTick;

    if (_end_SysTick > 0xFFFFFFFFU) {
        /* Overflow protection --------------------------------------------
            _end_SysTick = 0x0000_0001_0000_0000;
                                     ^- Overflow
            Shift to the beggining (32-bits) and wait till SysTick_msTicks
            is going to overflow and reach new value
            end_SysTick = 0x0000_0001;

        */
        end_SysTick = _end_SysTick >> 32;
    }

    while (SysTick_msTicks != end_SysTick) {
        __asm("NOP");
    }
}
