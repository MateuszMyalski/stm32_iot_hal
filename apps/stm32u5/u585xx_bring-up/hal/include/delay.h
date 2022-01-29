#ifndef DELAY_H
#define DELAY_H
#include <stdint.h>

/**
 * @brief Blocking delay, based on SysTick_msTicks variable.
 * @param delay - wait time in miliseconds
 * @return (void)
 */
void delay_ms(uint32_t delay);

#endif
