#ifndef LL_CRC_H
#define LL_CRC_H

#include <stdbool.h>

#include "ll_common.h"

/**************************************************************
 *               CRC GENERAL LOW-LEVEL FUNCTIONS              *
 **************************************************************/

/**
 * @brief Prepare to work CRC peripheral.
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_enable_AHB(CRC_TypeDef* ctx) {
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);
}

/**
 * @brief Stop CRC peripheral
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_disable_AHB(CRC_TypeDef* ctx) {
    CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);
}

/**
 * @brief Resets the crc algorithm.
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_reset(CRC_TypeDef* ctx) {
    SET_BIT(ctx->CR, CRC_CR_RESET);
}

/**************************************************************
 *                CRC IN/OUT LOW-LEVEL FUNCTIONS              *
 **************************************************************/

/**
 * @brief Reads calculated crc value.
 * @param ctx CMSIS CRC instance
 * @return Calculated crc.
 */
static inline uint32_t ll_crc_read_crc_reg(CRC_TypeDef* ctx) {
    return READ_REG(ctx->DR);
}

/**
 * @brief Update the crc.
 * @note Not even word blocks should be aligned to LSB.
 * @param ctx  CMSIS CRC instance
 * @param data Value that updates the crc
 */
static inline void ll_crc_write_data_reg(CRC_TypeDef* ctx, uint32_t data) {
    WRITE_REG(ctx->DR, data);
}

/**
 * @brief Saves the calculated crc value to the independent register.
 * @note Stored value is not affected to the peripheral reset.
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_store_crc(CRC_TypeDef* ctx) {
    uint32_t computed_crc = READ_REG(ctx->DR);
    WRITE_REG(ctx->IDR, computed_crc);
}

/**
 * @brief Read stored value in the independet register.
 * @param ctx CMSIS CRC instance
 * @return Stored crc value.
 */
static inline uint32_t ll_crc_read_stored_crc(CRC_TypeDef* ctx) {
    return READ_REG(ctx->IDR);
}

/**************************************************************
 *              CRC POLYNOMIAL LOW-LEVEL FUNCTIONS            *
 **************************************************************/

/**
 * @brief Set used polynomial in crc calculation.
 * @param ctx  CMSIS CRC instance
 * @param poly polynomial for crc. Default 0x4C11DB7 (Ethernet)
 */
static inline void ll_crc_set_poly(CRC_TypeDef* ctx, uint32_t poly) {
    WRITE_REG(ctx->POL, poly);
}

/**
 * @brief Sets polynomial size to 7 bits.
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_set_poly_size_7bit(CRC_TypeDef* ctx) {
    SET_BIT(ctx->POL, CRC_CR_POLYSIZE_1);
    SET_BIT(ctx->POL, CRC_CR_POLYSIZE_0);
}

/**
 * @brief Sets polynomial size to 8 bits.
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_set_poly_size_8bit(CRC_TypeDef* ctx) {
    SET_BIT(ctx->POL, CRC_CR_POLYSIZE_1);
    CLEAR_BIT(ctx->POL, CRC_CR_POLYSIZE_0);
}

/**
 * @brief Sets polynomial size to 16 bits.
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_set_poly_size_16bit(CRC_TypeDef* ctx) {
    CLEAR_BIT(ctx->POL, CRC_CR_POLYSIZE_1);
    SET_BIT(ctx->POL, CRC_CR_POLYSIZE_0);
}

/**
 * @brief Sets polynomial size to 32 bits.
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_set_poly_size_32bit(CRC_TypeDef* ctx) {
    CLEAR_BIT(ctx->POL, CRC_CR_POLYSIZE_1);
    CLEAR_BIT(ctx->POL, CRC_CR_POLYSIZE_0);
}

/**************************************************************
 *          CRC REVERSIGN IN/OUT LOW-LEVEL FUNCTIONS          *
 **************************************************************/

/**
 * @brief Output of the crc is reversed on bit level.
 * @note In eg. 0x11223344 -> 0x22CC4488
 * @param ctx          CMSIS CRC instance
 * @param out_reversed true to reverse the output, false to not reverse (default)
 */
static inline void ll_crc_set_out_reversed(CRC_TypeDef* ctx, bool out_reversed) {
    if (out_reversed) {
        SET_BIT(ctx->CR, CRC_CR_REV_OUT);
    } else {
        CLEAR_BIT(ctx->CR, CRC_CR_REV_OUT);
    }
}

/**
 * @brief Initialize the crc algorithm.
 * @param ctx        CMSIS CRC instance
 * @param init_value Initializaiton value
 */
static inline void ll_crc_init_crc(CRC_TypeDef* ctx, uint32_t init_value) {
    WRITE_REG(ctx->INIT, init_value);
}

/**
 * @brief Sets to not reverse the input data.
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_in_order_no_change(CRC_TypeDef* ctx) {
    CLEAR_BIT(ctx->CR, CRC_CR_REV_IN_1);
    CLEAR_BIT(ctx->CR, CRC_CR_REV_IN_0);
}

/**
 * @brief Reverse the input data by byte
 * @note E.g. 0x1A2B3C4D -> 0x58D43CB2
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_in_order_rev_by_byte(CRC_TypeDef* ctx) {
    CLEAR_BIT(ctx->CR, CRC_CR_REV_IN_1);
    SET_BIT(ctx->CR, CRC_CR_REV_IN_0);
}

/**
 * @brief Reverse the input data by half-word
 * @note E.g. 0x1A2B3C4D -> 0xD458B23C
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_in_order_rev_by_half_word(CRC_TypeDef* ctx) {
    SET_BIT(ctx->CR, CRC_CR_REV_IN_1);
    CLEAR_BIT(ctx->CR, CRC_CR_REV_IN_0);
}

/**
 * @brief Reverse the input data by full word
 * @note E.g. 0x1A2B3C4D -> 0xB23CD458
 * @param ctx CMSIS CRC instance
 */
static inline void ll_crc_in_order_rev_by_word(CRC_TypeDef* ctx) {
    SET_BIT(ctx->CR, CRC_CR_REV_IN_1);
    SET_BIT(ctx->CR, CRC_CR_REV_IN_0);
}

#endif
