#include "ll_common.h"

#define USART_APB_STABILIZATION_CYCLES 10U
#define USART_APB_RESET_CYCLES         10U


/**************************************************************
 *              USART GENERAL LOW-LEVEL FUNCTIONS             *
 *************************************************************/


/**
 * @brief Starts peripheral clock of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_apb_enable(USART_TypeDef *USART);

/**
 * @brief Stops peripheral clock of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_apb_disable(USART_TypeDef *USART);

/**
 * @brief Resets selected USART instance via RCC.
 * @param USART - CMSIS USART instance
 */
void ll_usart_reset(USART_TypeDef *USART);

/**
 * @brief Waits given number of clock cycles for APB to stabilize.
 * @param delay number of clock cycles to wait
 */
void ll_usart_apb_cycles_delay(uint32_t delay);

/**
 * @brief Sets desired baud in BRR of given USART instance
 * @param USART CMSIS USART instance
 * @param baud  desired baud 
 */
void ll_usart_set_baud_register(USART_TypeDef *USART, uint32_t baud);

/**
 * @brief Enables FIFO mode of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_fifo_mode_enable(USART_TypeDef *USART);

/**
 * @brief Disables FIFO mode of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_fifo_mode_disable(USART_TypeDef *USART);

/**
 * @brief Enables functionality of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_enable(USART_TypeDef *USART);

/**
 * @brief Confirms selected status flags of given USART
 *        instance by clearing them via interrupt flag
 *        clear register (ICR).
 * @param USART CMSIS USART instance
 * @param flags status flag selection. Flags can be
 *              concatenated using | logic operator.
 */
void ll_usart_confirm(USART_TypeDef *USART, uint32_t flags);


/**************************************************************
 *            USART TRANSMITTER LOW-LEVEL FUNCTIONS           *
 *************************************************************/

/**
 * @brief Enables transmitter of a given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_tx_enable(USART_TypeDef *USART);

/**
 * @brief  Checks if TDR of given USART instance is empty
 * @param  USART CMSIS USART instance
 * @return true - TDR is empty, false - otherwise
 */
bool ll_is_usart_tx_empty(USART_TypeDef *USART);

/**
 * @brief Writes data to TDR of a given USART instance
 * @param USART CMSIS USART instance
 * @param data  data to send
 */
void ll_usart_send_byte(USART_TypeDef *USART, uint8_t data);

/**
 * @brief  Checks if TX FIFO queue of given USART instance is not full
 * @param  USART CMSIS USART instance
 * @return true - TX FIFO not full, false - TX FIFO full
 */
bool is_usart_txfifo_not_full(USART_TypeDef *USART);

/**
 * @brief  Checks if transmission on given USART instance
 *         is complete. (All bits has been shifted out)
 * @param  USART CMSIS USART instance
 * @return true - TX is complete, false - otherwise
 */
bool ll_is_usart_tx_complete(USART_TypeDef *USART);


/**************************************************************
 *              USART RECEIVER LOW-LEVEL FUNCTIONS            *
 *************************************************************/

/**
 * @brief Enables receiver of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_rx_enable(USART_TypeDef *USART);

/**
 * @brief Enables RX timeout feature of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_rx_timeout_enable(USART_TypeDef *USART);

/**
 * @brief Disables RX timeout feature of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_rx_timeout_disable(USART_TypeDef *USART);

/**
 * @brief Sets RX timeout of given USART instance. This value must only be
 *        programmed once per received character.
 * @param USART   CMSIS USART instance
 * @param timeout Receiver timeout value in terms of number of bit duration.
 */
void ll_usart_rx_timeout_set(USART_TypeDef *USART, uint32_t timeout);

/**
 * @brief  Checks if RX data register (RDR) of given USART instance is empty
 * @param  USART CMSIS USART instance
 * @return true - RDR empy, false - otherwise
 */
bool ll_is_usart_rx_data(USART_TypeDef *USART);

/**
 * @brief  Checks if RX FIFO queue of given USART instance is empty
 * @param  USART CMSIS USART instance
 * @return true - RXFIFO not empy, false - RX FIFO is empty
 */
bool ll_is_usart_rxfifo_not_empty(USART_TypeDef *USART);

/**
 * @brief Enables given USART instance.
 * @param  USART CMSIS USART instance
 * @return 
 */
bool ll_is_usart_rx_idle(USART_TypeDef *USART);

/**
 * @brief Checks if RX timeout occured on given USART instance
 * @param USART CMSIS USART instance
 * @return true - timeout occured, false - otherwise
 */
bool ll_is_usart_rx_timeout(USART_TypeDef *USART);

/**
 * @brief Discards the data currently stored in RX data register
 *        of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_rx_discard(USART_TypeDef *USART);

/**
 * @brief Reads the data from RX data register of given USART instance
 * @param USART CMSIS USART instance
 * @return One byte of data read from RX data register.
 */
uint8_t ll_usart_read_byte(USART_TypeDef *USART);
