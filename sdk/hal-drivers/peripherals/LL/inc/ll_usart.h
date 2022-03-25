
#include "ll_common.h"

/**************************************************************
 *              USART GENERAL LOW-LEVEL FUNCTIONS             *
 *************************************************************/

/**
 * @brief Starts peripheral clock of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_pclk_start(USART_TypeDef *USART);

/**
 * @brief Stops peripheral clock of given USART instance.
 * @param USART CMSIS USART instance
 */
void ll_usart_pclk_stop(USART_TypeDef *USART);

/**
 * @brief Sets desired baud in BRR of given USART instance
 * @param USART CMSIS USART instance
 * @param baud  desired baud 
 */
static inline void ll_usart_set_baud_register(USART_TypeDef *USART, uint32_t baud) {
    USART->BRR = baud;
}

/**
 * @brief Enables FIFO mode of given USART instance.
 * @param USART CMSIS USART instance
 */
static inline void ll_usart_fifo_mode_enable(USART_TypeDef *USART) {
    SET_BIT(USART->CR1, USART_CR1_FIFOEN);
}

/**
 * @brief Disables FIFO mode of given USART instance.
 * @param USART CMSIS USART instance
 */
static inline void ll_usart_fifo_mode_disable(USART_TypeDef *USART) {
    CLEAR_BIT(USART->CR1, USART_CR1_FIFOEN);
}

/**
 * @brief Enables functionality of given USART instance.
 * @param USART CMSIS USART instance
 */
static inline void ll_usart_enable(USART_TypeDef *USART) {
    SET_BIT(USART->CR1, USART_CR1_UE);
}

/**
 * @brief Confirms selected status flags of given USART
 *        instance by clearing them via interrupt flag
 *        clear register (ICR).
 * @param USART CMSIS USART instance
 * @param flags status flag selection. Flags can be
 *              concatenated using | logic operator.
 */
static inline void ll_usart_confirm(USART_TypeDef *USART, uint32_t flags) {
    MODIFY_REG(USART->ICR, 0x000000, flags);
}

/**************************************************************
 *            USART TRANSMITTER LOW-LEVEL FUNCTIONS           *
 *************************************************************/

/**
 * @brief Enables transmitter of a given USART instance.
 * @param USART CMSIS USART instance
 */
static inline void ll_usart_tx_enable(USART_TypeDef *USART) {
    SET_BIT(USART->CR1, USART_CR1_TE);
}

/**
 * @brief Writes data to TDR of a given USART instance
 * @param USART CMSIS USART instance
 * @param data  data to send
 */
static inline void ll_usart_tx_write(USART_TypeDef *USART, uint8_t data) {
    USART->TDR = data;
}

/**
 * @brief  Checks if TDR of given USART instance is empty
 * @param  USART CMSIS USART instance
 * @return true - TDR is empty, false - otherwise
 */
static inline bool is_usart_tx_empty(USART_TypeDef *USART) {
    return (USART->ISR & USART_ISR_TXE_TXFNF) ? true : false;
}

/**
 * @brief  Checks if TX FIFO queue of given USART instance is not full
 * @param  USART CMSIS USART instance
 * @return true - TX FIFO not full, false - TX FIFO full
 */
static inline bool is_usart_txfifo_not_full(USART_TypeDef *USART) {
    return (USART->ISR & USART_ISR_TXE_TXFNF) ? true : false;
}

/**
 * @brief  Checks if transmission on given USART instance
 *         is complete. (All bits has been shifted out)
 * @param  USART CMSIS USART instance
 * @return true - TX is complete, false - otherwise
 */
static inline bool is_usart_tx_complete(USART_TypeDef *USART) {
    return (USART->ISR & USART_ISR_TC) ? true : false;
}


/**************************************************************
 *              USART RECEIVER LOW-LEVEL FUNCTIONS            *
 *************************************************************/


/**
 * @brief Enables receiver of given USART instance.
 * @param USART CMSIS USART instance
 */
static inline void ll_usart_rx_enable(USART_TypeDef *USART) {
    SET_BIT(USART->CR1, USART_CR1_RE);
}

/**
 * @brief Enables RX timeout feature of given USART instance.
 * @param USART CMSIS USART instance
 */
static inline void ll_usart_rx_timeout_emable(USART_TypeDef *USART) {
    SET_BIT(USART->CR2, USART_CR2_RTOEN);
}

/**
 * @brief Disables RX timeout feature of given USART instance.
 * @param USART CMSIS USART instance
 */
static inline void ll_usart_rx_timeout_disable(USART_TypeDef *USART) {
    CLEAR_BIT(USART->CR2, USART_CR2_RTOEN);
}

/**
 * @brief Sets RX timeout of given USART instance. This value must only be
 *        programmed once per received character.
 * @param USART   CMSIS USART instance
 * @param timeout Receiver timeout value in terms of number of bit duration.
 */
static inline void ll_usart_rx_timeout_set(USART_TypeDef *USART, uint32_t timeout) {
    USART->RTOR = (timeout & 0x00ffffff);
}

/**
 * @brief  Checks if RX data register (RDR) of given USART instance is empty
 * @param  USART CMSIS USART instance
 * @return true - RDR empy, false - otherwise
 */
static inline bool is_usart_rx_empty(USART_TypeDef *USART) {
    return (USART->ISR & USART_ISR_RXNE) ? true : false;
}

/**
 * @brief  Checks if RX FIFO queue of given USART instance is empty
 * @param  USART CMSIS USART instance
 * @return true - RXFIFO not empy, false - RX FIFO is empty
 */
static inline bool is_usart_rxfifo_not_empty(USART_TypeDef *USART) {
    return (USART->ISR & USART_ISR_RXNE_RXFNE) ? true : false;
}

/**
 * @brief Enables given USART instance.
 * @param  USART CMSIS USART instance
 * @return 
 */
static inline bool is_usart_rx_idle(USART_TypeDef *USART) {
    return (USART->ISR & USART_ISR_IDLE) ? true : false;
}

/**
 * @brief Checks if RX timeout occured on given USART instance
 * @param USART CMSIS USART instance
 * @return true - timeout occured, false - otherwise
 */
static inline bool is_usart_rx_timeout(USART_TypeDef *USART) {
    return (USART->ISR & USART_ISR_RTOF) ? true : false;
}

/**
 * @brief Discards the data currently stored in RX data register
 *        of given USART instance.
 * @param USART CMSIS USART instance
 */
static inline void ll_usart_rx_discard(USART_TypeDef *USART) {
    (void)(USART->RDR);
}

/**
 * @brief Reads the data from RX data register of given USART instance
 * @param USART CMSIS USART instance
 * @return One byte of data read from RX data register.
 */
static inline uint8_t ll_usart_rx_read(USART_TypeDef *USART) {
    return (uint8_t)(USART->RDR & 0xff);
}
