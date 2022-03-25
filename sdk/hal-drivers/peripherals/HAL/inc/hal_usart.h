
#ifndef USART_H
#define USART_H

#include "hal_common.h"

#define USART_DEFAULT_KCLK_SPEED  16000000U

#define USART_RX_IDLE       USART_ISR_IDLE
#define USART_RX_TIMEOUT    USART_ISR_RTOF
#define USART_RX_OVERRUN    USART_ISR_ORE
#define USART_TX_COMPLETE   USART_ISR_TC

typedef enum {
    USART_BAUD_9600,
    USART_BAUD_115200,
    USART_BAUD_230400
} USART_baud;

// TODO: add kernel clock source enum
// TODO: add clock prescaler enum


/**
 * @brief Starts peripheral clock of selected USART instance.
 * @param USART CMSIS USART instance
 */
void hal_usart_pclk_start(USART_TypeDef *USART);


/**
 * @brief Stops peripheral clock of selected USART instance.
 * @param USART CMSIS USART instance
 */
void hal_usart_pclk_stop(USART_TypeDef *USART);


/**
 * @brief Initializes registers of selected USART instance.
 * @param USART   CMSIS USART instance
 * @param baud    baud selection as defined in USART_baud.
 * @param io_port CMSIS GPIO port for TX and RX
 * @param tx_pin  transmitter pin number
 * @param rx_pin  receiver pin number
 * @return HAL_NO_ERR if success or error status
 */
hal_err_t hal_usart_init(USART_TypeDef *USART, USART_baud baud, GPIO_TypeDef *io_port, uint32_t tx_pin, uint32_t rx_pin);

/**
 * @brief Resets selected USART instance via RCC.
 * @param USART - CMSIS USART instance
 */
void hal_usart_reset(USART_TypeDef *USART);


/**
 * @brief Enables selected USART instance via RCC.
 * @param USART CMSIS USART instance
 */
void hal_usart_open(USART_TypeDef *USART);


/**
 * @brief Disables selected USART instance via RCC.
 * @param USART CMSIS USART instance
 */
void hal_usart_close(USART_TypeDef *USART);


/**
 * @brief Transmitts the bufer via selected USART instance.
 * @param USART     CMSIS USART instance
 * @param tx_buffer data buffer handle
 * @param nbytes    data buffer length
 * @return number of bytes transmitted
 */
int hal_usart_tx(USART_TypeDef *USART, uint8_t *tx_buffer, uint8_t nbytes);


/**
 * @brief Reads the incoming data from selected USART instance.
 * @param USART      CMSIS USART instance
 * @param tx_buffer  data buffer handle
 * @param nbytes     number of bytes to read
 * @return number of bytes received
 */
int hal_usart_rx(USART_TypeDef *USART, uint8_t *rx_buffer, uint8_t nbytes);

#endif // USART_H
