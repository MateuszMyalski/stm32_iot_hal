#include "ll_clock.h"

inline void ll_clock_hsi_on(RCC_TypeDef *rcc) {
    SET_BIT(RCC->CR, RCC_CR_HSION);
}

inline void ll_clock_hsi_off(RCC_TypeDef *rcc) {
    CLEAR_BIT(RCC->CR, RCC_CR_HSION);
}

inline void ll_clock_system_switch_MSIS(RCC_TypeDef *rcc) {
    CLEAR_BIT(RCC->CFGR1, RCC_CFGR1_SW_0);
    CLEAR_BIT(RCC->CFGR1, RCC_CFGR1_SW_1);
}

inline void ll_clock_system_switch_HSI16(RCC_TypeDef *rcc) {
    SET_BIT(RCC->CFGR1, RCC_CFGR1_SW_0);
    CLEAR_BIT(RCC->CFGR1, RCC_CFGR1_SW_1);
}

inline void ll_clock_system_switch_HSE(RCC_TypeDef *rcc) {
    CLEAR_BIT(RCC->CFGR1, RCC_CFGR1_SW_0);
    SET_BIT(RCC->CFGR1, RCC_CFGR1_SW_1);
}

inline void ll_clock_system_switch_PLL(RCC_TypeDef *rcc) {
    SET_BIT(RCC->CFGR1, RCC_CFGR1_SW_0);
    SET_BIT(RCC->CFGR1, RCC_CFGR1_SW_1);
}
