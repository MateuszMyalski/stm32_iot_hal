#ifndef LL_CLOCK_H
#define LL_CLOCK_H
#include <stdbool.h>

#include "ll_common.h"

void ll_clock_hsi_on(RCC_TypeDef *rcc);
void ll_clock_hsi_off(RCC_TypeDef *rcc);

void ll_clock_system_switch_MSIS(RCC_TypeDef *rcc);
void ll_clock_system_switch_HSI16(RCC_TypeDef *rcc);
void ll_clock_system_switch_HSE(RCC_TypeDef *rcc);
void ll_clock_system_switch_PLL(RCC_TypeDef *rcc);

#endif
