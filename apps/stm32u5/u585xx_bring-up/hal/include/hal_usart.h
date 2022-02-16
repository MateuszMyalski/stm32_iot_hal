
#ifndef USART_H
#define USART_H

#include "hal_common.h"

#define USART_DEFAULT_KCLK_SPEED  16000000U

typedef enum {
    USART_BAUDRATE_9600,
    USART_BAUDRATE_115200,
    USART_BAUDRATE_230400
} USART_baudrate;

// TODO: add kernel clock source enum
// TODO: add clock prescaler enum


/**
 * @brief Low-level: Starts peripheral clock of selected USART instance.
 * @param USART CMSIS USART instance
 */
void usart_pclk_start(USART_TypeDef *USART);


/**
 * @brief Low-level: Stops peripheral clock of selected USART instance.
 * @param USART CMSIS USART instance
 */
void usart_pclk_stop(USART_TypeDef *USART);


/**
 * @brief Low-level: Starts kernel clock of selected USART instance.
 * @param USART CMSIS USART instance
 */
void usart_kclk_start(USART_TypeDef *USART);


/**
 * @brief Low-level: Stops kernel clock of selected USART instance.
 * @param USART CMSIS USART instance
 */
void usart_kclk_stop(USART_TypeDef *USART);


/**
 * @brief Initializes registers of selected USART instance.
 * @param USART    CMSIS USART instance
 * @param baudrate baudrate selection as defined in USART_baudrate.
 */
int  hal_usart_init(USART_TypeDef *USART, USART_baudrate baudrate);


/**
 * @brief Resets selected USART instance via RCC.
 * @param USART - CMSIS USART instance
 */
void hal_usart_reset(USART_TypeDef *USART);


/**
 * @brief Enables selected USART instance via RCC.
 * @param USART CMSIS USART instance
 */
int hal_usart_open(USART_TypeDef *USART);


/**
 * @brief Disables selected USART instance via RCC.
 * @param USART CMSIS USART instance
 */
int hal_usart_close(USART_TypeDef *USART);


/**
 * @brief Transmitts the bufer via selected USART instance.
 * @param USART     CMSIS USART instance
 * @param tx_buffer data buffer handle
 * @param nbytes    data buffer length
 */
int hal_usart_tx(USART_TypeDef *USART, uint8_t *tx_buffer, uint8_t nbytes);


/**
 * @brief Reads the incoming data from selected USART instance.
 * @param USART      CMSIS USART instance
 * @param tx_buffer  data buffer handle
 * @param nbytes     number of bytes to read
 */
int hal_usart_rx(USART_TypeDef *USART, uint8_t *rx_buffer, uint8_t nbytes);

#endif // USART_H