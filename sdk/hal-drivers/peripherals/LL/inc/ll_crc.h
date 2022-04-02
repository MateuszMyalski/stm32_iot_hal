#ifndef LL_CRC_H
#define LL_CRC_H

#include <stdbool.h>

#include "ll_common.h"

static inline void ll_crc_enable_AHB(CRC_TypeDef* ctx) {
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);
}

static inline void ll_crc_disable_AHB(CRC_TypeDef* ctx) {
    CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);
}

static inline uint32_t ll_crc_read_crc_reg(CRC_TypeDef* ctx) {
    return READ_REG(ctx->DR);
}

static inline void ll_crc_write_data_reg(CRC_TypeDef* ctx, uint32_t data) {
    WRITE_REG(ctx->DR, data);
}

static inline void ll_crc_set_poly_size_7bit(CRC_TypeDef* ctx) {
    SET_BIT(ctx->POL, CRC_CR_POLYSIZE_1);
    SET_BIT(ctx->POL, CRC_CR_POLYSIZE_0);
}

static inline void ll_crc_set_poly_size_8bit(CRC_TypeDef* ctx) {
    SET_BIT(ctx->POL, CRC_CR_POLYSIZE_1);
    CLEAR_BIT(ctx->POL, CRC_CR_POLYSIZE_0);
}

static inline void ll_crc_set_poly_size_16bit(CRC_TypeDef* ctx) {
    CLEAR_BIT(ctx->POL, CRC_CR_POLYSIZE_1);
    SET_BIT(ctx->POL, CRC_CR_POLYSIZE_0);
}

static inline void ll_crc_set_poly_size_32bit(CRC_TypeDef* ctx) {
    CLEAR_BIT(ctx->POL, CRC_CR_POLYSIZE_1);
    CLEAR_BIT(ctx->POL, CRC_CR_POLYSIZE_0);
}

static inline void ll_crc_store_crc(CRC_TypeDef* ctx) {
    uint32_t computed_crc = READ_REG(ctx->DR);
    WRITE_REG(ctx->IDR, computed_crc);
}

static inline uint32_t ll_crc_read_stored_crc(CRC_TypeDef* ctx) {
    return READ_REG(ctx->IDR);
}

static inline void ll_crc_reset(CRC_TypeDef* ctx) {
    SET_BIT(ctx->CR, CRC_CR_RESET);
}

static inline void ll_crc_set_out_reversed(CRC_TypeDef* ctx, bool out_reversed) {
    if (out_reversed) {
        SET_BIT(ctx->CR, CRC_CR_REV_OUT);
    } else {
        CLEAR_BIT(ctx->CR, CRC_CR_REV_OUT);
    }
}

static inline void ll_crc_init_crc(CRC_TypeDef* ctx, uint32_t init_value) {
    WRITE_REG(ctx->INIT, init_value);
}

static inline void ll_crc_in_order_no_change(CRC_TypeDef* ctx) {
    CLEAR_BIT(ctx->CR, CRC_CR_REV_IN_1);
    CLEAR_BIT(ctx->CR, CRC_CR_REV_IN_0);
}

static inline void ll_crc_in_order_rev_by_byte(CRC_TypeDef* ctx) {
    CLEAR_BIT(ctx->CR, CRC_CR_REV_IN_1);
    SET_BIT(ctx->CR, CRC_CR_REV_IN_0);
}

static inline void ll_crc_in_order_rev_by_half_word(CRC_TypeDef* ctx) {
    SET_BIT(ctx->CR, CRC_CR_REV_IN_1);
    CLEAR_BIT(ctx->CR, CRC_CR_REV_IN_0);
}

static inline void ll_crc_in_order_rev_by_word(CRC_TypeDef* ctx) {
    SET_BIT(ctx->CR, CRC_CR_REV_IN_1);
    SET_BIT(ctx->CR, CRC_CR_REV_IN_0);
}

static inline void ll_crc_set_poly(CRC_TypeDef* ctx, uint32_t poly) {
    WRITE_REG(ctx->POL, poly);
}

#endif
