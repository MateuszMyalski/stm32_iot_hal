#ifndef USART_H
#define USART_H

#include "hal_common.h"
#include <stddef.h>

#define USART_DEFAULT_KCLK_SPEED  16000000U

#define USART_RX_IDLE       USART_ISR_IDLE
#define USART_RX_TIMEOUT    USART_ISR_RTOF
#define USART_RX_OVERRUN    USART_ISR_ORE
#define USART_TX_COMPLETE   USART_ISR_TC

/**
 * @brief USART supported baud
 */
typedef enum {
    USART_BAUD_9600,
    USART_BAUD_115200,
    USART_BAUD_230400
} USART_baud;

/**
 * @brief USART operating mode
 */
typedef enum {
    USART_OPMODE_NORMAL, /* Normal operation */
    USART_OPMODE_FIFO    /* FIFO operation. Enables queue on both RX and TX */
} USART_opmode;

/**
 * @brief USART runtime configurable parameters
 */
typedef enum {

    /* [NULL] Peripheral receiver timeout enable. */
    USART_IOCTL_PERIPH_TIMEOUT_ENABLE,

    /* [NULL] Peripheral receiver timeout disable. */
    USART_IOCTL_PERIPH_TIMEOUT_DISABLE,

    /** [uint32_t] Peripheral receiver timeout. User must specify
     * the timeout value measured in bit duration. (Depends on baud)
     * */
    USART_IOCTL_PERIPH_TIMEOUT,

    /** [uint32_t] Blocking read period. User must specify the timeout
     * value in miliseconds 
     */
    USART_IOCTL_BLOCKING_TIMEOUT

    /*TODO: Add FIFO thresholds, interrupts, DMA, etc*/

} USART_ioctl;

// TODO: add kernel clock source enum
// TODO: add clock prescaler enum

/**
 * @brief Initializes selected USART instance.
 * @param USART   CMSIS USART instance
 * @param baud    baud selection as defined in USART_baud.
 * @param io_port CMSIS GPIO port for TX and RX
 * @param tx_pin  transmitter pin number
 * @param rx_pin  receiver pin number
 * @return HAL_NO_ERR if success or error code otherwise
 */
hal_err_t hal_usart_open(USART_TypeDef *USART, USART_baud baud, USART_opmode mode);


/**
 * @brief Resets selected USART instance via RCC.
 * @param USART CMSIS USART instance
 */
void hal_usart_reset(USART_TypeDef *USART);


/**
 * @brief Deinitializes selected USART instance.
 * @param USART CMSIS USART instance
 */
void hal_usart_close(USART_TypeDef *USART);


/**
 * @brief Manipulates selected USART instance parameters
 * @param  USART CMSIS USART instance
 * @param  param feature to enable or parameter to set
 * @param  value parameter value
 * @return HAL_NO_ERR if success or error code otherwise
 */
hal_err_t hal_usart_ioctl(USART_TypeDef *USART, USART_ioctl param, void *value);


/**
 * @brief Transmitts the bufer via selected USART instance.
 * @param USART     CMSIS USART instance
 * @param tx_buffer data buffer handle
 * @param nbytes    data buffer length
 * @return number of bytes transmitted
 */
int hal_usart_tx(USART_TypeDef *USART, uint8_t *tx_buffer, size_t nbytes);


/**
 * @brief Transmitts single character via selected USART instance.
 * @param USART CMSIS USART instance
 * @param c     character to send
 * @return HAL_NO_ERR if success or error code otherwise
 */
hal_err_t hal_usart_putchar(USART_TypeDef *USART, char c);


/**
 * @brief Reads the incoming data from selected USART instance.
 * @param USART      CMSIS USART instance
 * @param tx_buffer  data buffer handle
 * @param nbytes     number of bytes to read
 * @return number of bytes received
 */
int hal_usart_rx(USART_TypeDef *USART, uint8_t *rx_buffer, size_t nbytes);

#endif // USART_H
