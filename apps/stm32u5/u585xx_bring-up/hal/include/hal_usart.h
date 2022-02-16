
#ifndef USART_H
#define USART_H

#include "hal_common.h"

typedef enum {
    USART_BAUDRATE_9600,
    USART_BAUDRATE_115200,
    USART_BAUDRATE_230400
} USART_baudrate;

typedef enum {
    USART_OVERSAMPLE_08,
    USART_OVERSAMPLE_16
} USART_oversampling;

// TODO: add kernel clock source enum
// TODO: add clock prescaler enum

// low level peripheral clock control
void _usart_pclk_start(USART_TypeDef *USART);
void _usart_pclk_stop(USART_TypeDef *USART);

// low level kernel clock control (worth implementing?)
void _usart_kclk_start(USART_TypeDef *USART);
void _usart_kclk_stop(USART_TypeDef *USART);

int  hal_usart_init(USART_TypeDef *USART, USART_baudrate baudrate, USART_oversampling oversampling);
void hal_usart_reset(USART_TypeDef *USART);

int hal_usart_open(USART_TypeDef *USART);
int hal_usart_close(USART_TypeDef *USART);

int hal_usart_tx(USART_TypeDef *USART, uint8_t *tx_buffer, uint8_t nbytes);
int hal_usart_rx(USART_TypeDef *USART, uint8_t *rx_buffer, uint8_t nbytes);

#endif // USART_H