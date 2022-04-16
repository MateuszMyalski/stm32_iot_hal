#include "ll_usart.h"

/**************************************************************
 *              USART GENERAL LOW-LEVEL FUNCTIONS             *
 *************************************************************/

void ll_usart_apb_enable(USART_TypeDef *USART) {

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
    ll_usart_apb_cycles_delay(USART_APB_STABILIZATION_CYCLES);
}


void ll_usart_reset(USART_TypeDef *USART) {
    
    switch ((intptr_t)USART) {
        case USART1_BASE:
            SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
            ll_usart_apb_cycles_delay(USART_APB_RESET_CYCLES);
            CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
            break;

        case USART2_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST);
            ll_usart_apb_cycles_delay(USART_APB_RESET_CYCLES);
            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST);
            break;

        case USART3_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST);
            ll_usart_apb_cycles_delay(USART_APB_RESET_CYCLES);
            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST);
            break;

        case UART4_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST);
            ll_usart_apb_cycles_delay(USART_APB_RESET_CYCLES);
            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST);
            break;

        case UART5_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST);
            ll_usart_apb_cycles_delay(USART_APB_RESET_CYCLES);
            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST);
            break;

        default:
            break;
    }
}


void ll_usart_apb_disable(USART_TypeDef *USART) {
    
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


inline void ll_usart_apb_cycles_delay(uint32_t delay) {
    while (delay--) {
        // Wait for APB stabilization
        asm("nop");
    }
}


inline void ll_usart_set_baud_register(USART_TypeDef *USART, uint32_t baud) {
    USART->BRR = baud;
}


inline void ll_usart_fifo_mode_enable(USART_TypeDef *USART) {
    SET_BIT(USART->CR1, USART_CR1_FIFOEN);
}


inline void ll_usart_fifo_mode_disable(USART_TypeDef *USART) {
    CLEAR_BIT(USART->CR1, USART_CR1_FIFOEN);
}


inline void ll_usart_enable(USART_TypeDef *USART) {
    SET_BIT(USART->CR1, USART_CR1_UE);
}


inline void ll_usart_confirm(USART_TypeDef *USART, uint32_t flags) {
    MODIFY_REG(USART->ICR, 0x000000, flags);
}


/**************************************************************
 *            USART TRANSMITTER LOW-LEVEL FUNCTIONS           *
 *************************************************************/

inline void ll_usart_tx_enable(USART_TypeDef *USART) {
    SET_BIT(USART->CR1, USART_CR1_TE);
}


inline bool ll_is_usart_tx_empty(USART_TypeDef *USART) {
    return READ_BIT(USART->ISR, USART_ISR_TXE_TXFNF);
}


inline void ll_usart_send_byte(USART_TypeDef *USART, uint8_t data) {
    USART->TDR = data;
    while (!ll_is_usart_tx_empty(USART)) {
    // wait until data register becomes empty
    }
}


inline bool is_usart_txfifo_not_full(USART_TypeDef *USART) {
    return READ_BIT(USART->ISR, USART_ISR_TXE_TXFNF);
}

inline bool ll_is_usart_tx_complete(USART_TypeDef *USART) {
    return READ_BIT(USART->ISR, USART_ISR_TC);
}


/**************************************************************
 *              USART RECEIVER LOW-LEVEL FUNCTIONS            *
 *************************************************************/

inline void ll_usart_rx_enable(USART_TypeDef *USART) {
    SET_BIT(USART->CR1, USART_CR1_RE);
}


inline void ll_usart_rx_timeout_enable(USART_TypeDef *USART) {
    SET_BIT(USART->CR2, USART_CR2_RTOEN);
}


inline void ll_usart_rx_timeout_disable(USART_TypeDef *USART) {
    CLEAR_BIT(USART->CR2, USART_CR2_RTOEN);
}


inline void ll_usart_rx_timeout_set(USART_TypeDef *USART, uint32_t timeout) {
    USART->RTOR = (timeout & 0x00ffffff);
}


inline bool ll_is_usart_rx_data(USART_TypeDef *USART) {
    return READ_BIT(USART->ISR, USART_ISR_RXNE);
}


inline bool ll_is_usart_rxfifo_not_empty(USART_TypeDef *USART) {
    return READ_BIT(USART->ISR, USART_ISR_RXNE_RXFNE);
}


inline bool ll_is_usart_rx_idle(USART_TypeDef *USART) {
    return READ_BIT(USART->ISR, USART_ISR_IDLE);
}


inline bool ll_is_usart_rx_timeout(USART_TypeDef *USART) {
    return READ_BIT(USART->ISR, USART_ISR_RTOF);
}


inline void ll_usart_rx_discard(USART_TypeDef *USART) {
    (void)(USART->RDR);
}


inline uint8_t ll_usart_read_byte(USART_TypeDef *USART) {
    return (uint8_t)(USART->RDR & 0xff);
}
