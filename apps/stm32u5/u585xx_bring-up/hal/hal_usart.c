
#include "hal_usart.h"

void _usart_pclk_start(USART_TypeDef *USART)
{
    switch ((intptr_t)USART) {
        case USART1_BASE:
            SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
            break;
        case USART2_BASE:
            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART2EN);
            break;
        case USART3_BASE:
            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_USART3EN);
            break;
        case UART4_BASE:
            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART4EN);
            break;
        case UART5_BASE:
            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_UART5EN);
            break;
        default:
            break;
    }
}


void _usart_pclk_stop(USART_TypeDef *USART)
{
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

void _usart_kclk_start(USART_TypeDef *USART)
{
    // implement me
}


void _usart_kclk_stop(USART_TypeDef *USART)
{
    // implement me
}

int hal_usart_init(USART_TypeDef *USART, USART_baudrate baudrate, USART_oversampling oversampling)
{
   // todo: implement API obtain usart kernel clock
   // kernel clock = (pclk or hsi16 or lse or sysclk) x usart_prescaler

    uint32_t usart_kernel_clk = 16000000;
    uint16_t usartdiv         = 0x0000;
    uint8_t  prescaler        = 0x01;
    uint8_t  temp             = 0x00;

    hal_usart_reset(USART);
    _usart_pclk_start(USART);

    /* Ref: RM0456: 57.5.8 USART baud rate generation */

    /*  1.
    Program the M bits in USART_CR1 to define the word length.
    M[1:0] = 00: 1 start bit, 8 Data bits, n Stop bit (default)
    */

    /*  2.
    Select the desired baud rate using the USART_BRR register.
    */
    usartdiv = usart_kernel_clk / prescaler;
    
    if (oversampling == USART_OVERSAMPLE_08) {
        usartdiv = 2 * usartdiv / baudrate;
        temp = usartdiv & 0x0007;
        usartdiv = (usartdiv & 0xFFF8) | (temp >> 1);
    }
    else {
        usartdiv = usartdiv / baudrate;
    }

    USART->BRR = usartdiv;

    /*  3.
    Program the number of stop bits in USART_CR2.
    STOP[1:0] = 00: 1 stop bit (default)
    */

    /*   4,
    Enable the USART by writing the UE bit in USART_CR1 register to 1.
    */
    SET_BIT(USART->CR1, USART_CR1_UE);

    _usart_pclk_stop(USART);

    return 0;
}


void hal_usart_reset(USART_TypeDef *USART)
{
    switch ((intptr_t)USART) {
        case USART1_BASE:
            SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
            break;
        case USART2_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART2RST);
            break;
        case USART3_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_USART3RST);
            break;
        case UART4_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART4RST);
            break;
        case UART5_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_UART5RST);
            break;
        default:
            break;
    }
}


int hal_usart_open(USART_TypeDef *USART)
{
    return 0;
}


int hal_usart_close(USART_TypeDef *USART)
{
    return 0;
}


int hal_usart_tx(USART_TypeDef *USART, uint8_t *tx_buffer, uint8_t nbytes)
{
    _usart_pclk_start(USART);

    /* Ref: RM0456: 57.5.8 USART baud rate generation */

    /*  6.
    Set the TE bit in USART_CR1 to send an idle frame as first transmission.
    */
    SET_BIT(USART->CR1, USART_CR1_TE);

    /*  7.
    Write the data to send in the USART_TDR register. Repeat this for each
    data to be transmitted in case of single buffer.
    */
    // consider using fifo mode with interrupts here
    for(int i=0; i<nbytes; ++i) {
        USART->TDR = tx_buffer[i];

        // blocking wait until tx buffer empty.
        while(USART->ISR & USART_ISR_TXE)
            ;
    }

    /*  8.
    When the last data is written to the USART_TDR register, wait until TC=1.
    – When FIFO mode is disabled, this indicates that the transmission
    of the last frame is complete.
    – When FIFO mode is enabled, this indicates that both TXFIFO and shift
    register are empty. This check is required to avoid corrupting the last
    transmission when the USART is disabled or enters Halt mode.
    */

    _usart_pclk_stop(USART);

    return 0;
}


int hal_usart_rx(USART_TypeDef *USART, uint8_t *rx_buffer, uint8_t nbytes)
{
    return 0;
}