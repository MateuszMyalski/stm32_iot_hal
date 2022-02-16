
#include "hal_usart.h"
#include "delay.h"

// usart kernel clock frequency
static uint32_t usart_kernel_clk = USART_DEFAULT_KCLK_SPEED;
// todo: implement API obtain usart kernel clock

void usart_pclk_start(USART_TypeDef *USART) {
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
    delay_ms(2);
}

void usart_pclk_stop(USART_TypeDef *USART) {
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
    delay_ms(2);
}

void usart_kclk_start(USART_TypeDef *USART) {
    // implement me
}

void usart_kclk_stop(USART_TypeDef *USART) {
    // implement me
}

int hal_usart_init(USART_TypeDef *USART, USART_baudrate baudrate) {

    uint32_t usartdiv = 0x0000;

    hal_usart_open(USART);

    usartdiv = (usart_kernel_clk);

    switch (baudrate) {
        case USART_BAUDRATE_230400:
            usartdiv = (usartdiv / 230400) + 1;
            break;
        case USART_BAUDRATE_115200:
            usartdiv = (usartdiv / 115200) + 1;
            break;
        case USART_BAUDRATE_9600:
            usartdiv = (usartdiv / 9600) + 1;
            break;
        default:
            break;
    }

    USART->BRR = usartdiv;

    SET_BIT(USART->CR1, USART_CR1_FIFOEN);
    SET_BIT(USART->CR1, USART_CR1_TE);  //      Enable transmitter
    SET_BIT(USART->CR1, USART_CR1_UE);  // Enable USART peripheral

    hal_usart_close(USART);

    return 0;
}

void hal_usart_reset(USART_TypeDef *USART) {

    switch ((intptr_t)USART) {
        case USART1_BASE:
            SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
            CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
            break;
        case USART2_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST);
            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST);
            break;
        case USART3_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST);
            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST);
            break;
        case UART4_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST);
            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST);
            break;
        case UART5_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST);
            CLEAR_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST);
            break;
        default:
            break;
    }
    delay_ms(2);
}


int hal_usart_open(USART_TypeDef *USART) {
    usart_pclk_start(USART);
    return 0;
}


int hal_usart_close(USART_TypeDef *USART) {
    usart_pclk_stop(USART);
    return 0;
}


int hal_usart_tx(USART_TypeDef *USART, uint8_t *tx_buffer, uint8_t nbytes) {

    hal_usart_open(USART);

    for (int i = 0; i < nbytes; i++) {

        USART->TDR = tx_buffer[i];

        // wait until data register becomes empty
        while (!(USART->ISR & USART_ISR_TXE_TXFNF))
            __asm("NOP");
    }

    // wait untill the last frame leaves the shift register
    while (!(USART->ISR & USART_ISR_TC))
        __asm("NOP");

    hal_usart_close(USART);
    return 0;
}


int hal_usart_rx(USART_TypeDef *USART, uint8_t *rx_buffer, uint8_t nbytes) {
    return 0;
}