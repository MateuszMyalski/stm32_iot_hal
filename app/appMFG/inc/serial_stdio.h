#ifndef SERIAL_STDIO_H
#define SERIAL_STDIO_H

#include "hal_usart.h"

/** @brief Enables standard input/output on selected USART peripheral
 *  @param instance CMSIS USART instance
 */
void serial_stdio_init(USART_TypeDef * instance);

#endif //SERIAL_STDIO_H