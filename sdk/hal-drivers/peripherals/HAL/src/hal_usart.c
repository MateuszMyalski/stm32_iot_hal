
#include "ll_usart.h"
#include "hal_usart.h"

#include "hal_gpio.h"
#include "delay.h"


// usart kernel clock frequency
static uint32_t usart_kernel_clk = USART_DEFAULT_KCLK_SPEED;
// todo: implement API obtain usart kernel clock



/**
 * @brief Initializes IO lines for selected USART instance.
 * @param USART   CMSIS USART instance
 * @param io_port CMSIS GPIO port for TX and RX
 * @param tx_pin  transmitter pin number
 * @param rx_pin  receiver pin number
 */
static void hal_usart_ioctl(USART_TypeDef *USART, GPIO_TypeDef *io_port, uint32_t tx_pin, uint32_t rx_pin) {

    hal_gpio_open(io_port);

    hal_gpio_ioctl(io_port, tx_pin, gpio_ioctl_af_7);
    hal_gpio_ioctl(io_port, tx_pin, gpio_ioctl_alternate);
    hal_gpio_ioctl(io_port, tx_pin, gpio_ioctl_push_pull);

    hal_gpio_ioctl(io_port, rx_pin, gpio_ioctl_af_7);
    hal_gpio_ioctl(io_port, rx_pin, gpio_ioctl_alternate);
    hal_gpio_ioctl(io_port, rx_pin, gpio_ioctl_push_pull);
}


void hal_usart_open(USART_TypeDef *USART) {
    ll_usart_pclk_start(USART);
}


void hal_usart_close(USART_TypeDef *USART) {
    ll_usart_pclk_stop(USART);
}


hal_err_t hal_usart_init(USART_TypeDef *USART, USART_baud baud, GPIO_TypeDef *io_port, uint32_t tx_pin, uint32_t rx_pin) {

    uint32_t usartdiv = 0x0000;

    // initialize gpios
    hal_usart_ioctl(USART, io_port, tx_pin, rx_pin);

    usartdiv = (usart_kernel_clk);

    switch (baud) {
        case USART_BAUD_230400:
            usartdiv = (usartdiv / 230400) + 1;
            ll_usart_rx_timeout_set(USART, 2304);
            break;

        case USART_BAUD_115200:
            usartdiv = (usartdiv / 115200) + 1;
            ll_usart_rx_timeout_set(USART, 1152);
            break;

        case USART_BAUD_9600:
            usartdiv = (usartdiv / 9600) + 1;
            ll_usart_rx_timeout_set(USART, 96);
            break;

        default:
            break;
    }

    ll_usart_set_baud_register(USART, usartdiv);

    ll_usart_tx_enable(USART);
    ll_usart_rx_enable(USART);

    ll_usart_enable(USART);

    return HAL_NO_ERR;
}


int hal_usart_tx(USART_TypeDef *USART, uint8_t *tx_buffer, uint8_t nbytes) {

    for (int i = 0; i < nbytes; ++i) {
        ll_usart_tx_write(USART, tx_buffer[i]);

        while (!is_usart_tx_empty(USART)) {
            // wait until data register becomes empty
        }
    }

    while (!is_usart_tx_complete(USART)) {
        // wait untill the last frame leaves the shift register
    }

    ll_usart_confirm(USART, USART_TX_COMPLETE);

    return HAL_NO_ERR;
}


int hal_usart_rx(USART_TypeDef *USART, uint8_t *rx_buffer, uint8_t nbytes) {

    int i;

    ll_usart_rx_timeout_emable(USART);  // Enable receiver timeout

    for (i = 0; i < nbytes; ++i) {
        while (!is_usart_rx_empty(USART)) {
            if (is_usart_rx_timeout(USART)) {
                goto exit;
            }
        }
        rx_buffer[i] = ll_usart_rx_read(USART);
    }

    while (!is_usart_rx_idle(USART)) {
        if (is_usart_rx_timeout(USART)) {

            ll_usart_rx_discard(USART);
            goto exit;
        }
    }

exit:

    ll_usart_confirm(USART, USART_RX_TIMEOUT | USART_RX_OVERRUN | USART_RX_IDLE);

    ll_usart_rx_timeout_disable(USART);
    ll_usart_rx_discard(USART);

    return i; // return number od bytes read
}
