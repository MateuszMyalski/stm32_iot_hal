#include "ll_usart.h"
#include "hal_usart.h"


// usart kernel clock frequency
static uint32_t usart_kernel_clk = USART_DEFAULT_KCLK_SPEED;
// todo: implement API obtain usart kernel clock


hal_err_t hal_usart_open(USART_TypeDef *USART, USART_baud baud, USART_opmode mode) {

    uint32_t usartdiv = 0x0000;

    ll_usart_apb_enable(USART);
    usartdiv = (usart_kernel_clk);

    switch (baud) {
        case USART_BAUD_230400:
            usartdiv = (usartdiv / 230400) + 1;
            break;

        case USART_BAUD_115200:
            usartdiv = (usartdiv / 115200) + 1;
            break;

        case USART_BAUD_9600:
            usartdiv = (usartdiv / 9600) + 1;
            break;

        default:
            return HAL_ERR_PARAMS;
    }

    ll_usart_set_baud_register(USART, usartdiv);

    if(mode == USART_OPMODE_FIFO)
        ll_usart_fifo_mode_enable(USART);

    ll_usart_tx_enable(USART);
    ll_usart_rx_enable(USART);

    ll_usart_enable(USART);

    return HAL_NO_ERR;
}


void hal_usart_reset(USART_TypeDef *USART) {
    ll_usart_reset(USART);
}


hal_err_t hal_usart_ioctl(USART_TypeDef *USART, USART_ioctl param, void *value) {

    switch (param) {

        case USART_IOCTL_PERIPH_TIMEOUT_ENABLE:
            ll_usart_rx_timeout_enable(USART);
            break;

        case USART_IOCTL_PERIPH_TIMEOUT_DISABLE:
            ll_usart_rx_timeout_disable(USART);
            break;

        case USART_IOCTL_PERIPH_TIMEOUT:
            if(NULL == value)
                return HAL_ERR_PARAMS;
            ll_usart_rx_timeout_set(USART, *((uint32_t *)value));
            break;

        default:
            return HAL_ERR_PARAMS;
    }

    return HAL_NO_ERR;
 }


void hal_usart_close(USART_TypeDef *USART) {
    ll_usart_reset(USART);
    ll_usart_apb_disable(USART);
}


int hal_usart_tx(USART_TypeDef *USART, uint8_t *tx_buffer, size_t nbytes) {

    int i;

    for (i = 0; i < nbytes; ++i) {
        ll_usart_send_byte(USART, tx_buffer[i]);
    }

    while (!ll_is_usart_tx_complete(USART)) { 

        /** RM0456 p.2263:  Character transmission procedure, point 8:
         * When the  last data is  written to the  USART_TDR register,
         * wait until TC=1. This check is required to avoid corrupting
         * the last transmission when the  USART is disabled or enters
         * Halt mode.                                               */
        asm("nop");
    }

    ll_usart_confirm(USART, USART_TX_COMPLETE);

    return i;
}


hal_err_t hal_usart_putchar(USART_TypeDef *USART, char c) {

    ll_usart_send_byte(USART, (uint8_t)c);


    while (!ll_is_usart_tx_complete(USART)) { 

        /** RM0456 p.2263:  Character transmission procedure, point 8:
         * When the  last data is  written to the  USART_TDR register,
         * wait until TC=1. This check is required to avoid corrupting
         * the last transmission when the  USART is disabled or enters
         * Halt mode.                                               */
        asm("nop");
    }

    ll_usart_confirm(USART, USART_TX_COMPLETE);

    return HAL_NO_ERR;
}


int hal_usart_rx(USART_TypeDef *USART, uint8_t *rx_buffer, size_t nbytes) {

    int i;

    for (i = 0; i < nbytes; ++i) {
        while (!ll_is_usart_rx_data(USART)) {
            if (ll_is_usart_rx_timeout(USART)) {
                goto exit;
            }
        }
        rx_buffer[i] = ll_usart_read_byte(USART);
    }

    while (!ll_is_usart_rx_idle(USART)) {
        if (ll_is_usart_rx_timeout(USART)) {

            ll_usart_rx_discard(USART);
            goto exit;
        }
    }

exit:

    ll_usart_confirm(USART, USART_RX_TIMEOUT | USART_RX_OVERRUN | USART_RX_IDLE);
    ll_usart_rx_discard(USART);

    return i; // return number od bytes read
}
