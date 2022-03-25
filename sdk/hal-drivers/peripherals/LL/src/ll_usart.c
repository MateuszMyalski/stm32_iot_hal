
#include "ll_usart.h"

void ll_usart_pclk_start(USART_TypeDef *USART) {

    switch ((intptr_t)USART) {
        case USART1_BASE_NS:
            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
            break;

        case USART2_BASE_NS:
            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN);
            break;

        case USART3_BASE_NS:
            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN);
            break;

        case UART4_BASE_NS:
            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN);
            break;

        case UART5_BASE_NS:
            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN);
            break;

        default:
            break;
    }
}

void ll_usart_pclk_stop(USART_TypeDef *USART) {
    
    switch ((intptr_t)USART) {
        case USART1_BASE:
            CLEAR_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
            break;

        case USART2_BASE:
            CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN);
            break;

        case USART3_BASE:
            CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN);
            break;

        case UART4_BASE:
            CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN);
            break;

        case UART5_BASE:
            CLEAR_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN);
            break;

        default:
            break;
    }
}
