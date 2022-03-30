#ifndef LL_CRC_H
#define LL_CRC_H

#include <stdbool.h>

#include "ll_common.h"

static inline void ll_crc_enable_AHB() {
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);
}

static inline void ll_crc_disable_AHB() {
    CLEAR_BIT(RCC->AHB1ENR, RCC_AHB1ENR_CRCEN);
}

static inline uint32_t ll_crc_read_crc_reg() {
    return READ_REG(CRC->DR);
}

static inline void ll_crc_write_data_reg(uint32_t data) {
    WRITE_REG(CRC->DR, data);
}

static inline void ll_crc_set_poly_size_7bit() {
    SET_BIT(CRC->POL, CRC_CR_POLYSIZE_1);
    SET_BIT(CRC->POL, CRC_CR_POLYSIZE_0);
}

static inline void ll_crc_set_poly_size_8bit() {
    SET_BIT(CRC->POL, CRC_CR_POLYSIZE_1);
    CLEAR_BIT(CRC->POL, CRC_CR_POLYSIZE_0);
}

static inline void ll_crc_set_poly_size_16bit() {
    CLEAR_BIT(CRC->POL, CRC_CR_POLYSIZE_1);
    SET_BIT(CRC->POL, CRC_CR_POLYSIZE_0);
}

static inline void ll_crc_set_poly_size_32bit() {
    CLEAR_BIT(CRC->POL, CRC_CR_POLYSIZE_1);
    CLEAR_BIT(CRC->POL, CRC_CR_POLYSIZE_0);
}

static inline void ll_crc_store_crc() {
    uint32_t computed_crc = READ_REG(CRC->DR);
    WRITE_REG(CRC->IDR, computed_crc);
}

static inline uint32_t ll_crc_read_stored_crc() {
    return READ_REG(CRC->IDR);
}

static inline void ll_crc_reset() {
    SET_BIT(CRC->CR, CRC_CR_RESET);
}

static inline void ll_crc_set_out_reversed(bool out_reversed) {
    if (out_reversed) {
        SET_BIT(CRC->CR, CRC_CR_REV_OUT);
    } else {
        CLEAR_BIT(CRC->CR, CRC_CR_REV_OUT);
    }
}

static inline void ll_crc_init_crc(uint32_t init_value) {
    WRITE_REG(CRC->INIT, init_value);
}

static inline void ll_crc_in_order_no_change() {
    CLEAR_BIT(CRC->CR, CRC_CR_REV_IN_1);
    CLEAR_BIT(CRC->CR, CRC_CR_REV_IN_0);
}

static inline void ll_crc_in_order_rev_by_byte() {
    CLEAR_BIT(CRC->CR, CRC_CR_REV_IN_1);
    SET_BIT(CRC->CR, CRC_CR_REV_IN_0);
}

static inline void ll_crc_in_order_rev_by_half_word() {
    SET_BIT(CRC->CR, CRC_CR_REV_IN_1);
    CLEAR_BIT(CRC->CR, CRC_CR_REV_IN_0);
}

static inline void ll_crc_in_order_rev_by_word() {
    SET_BIT(CRC->CR, CRC_CR_REV_IN_1);
    SET_BIT(CRC->CR, CRC_CR_REV_IN_0);
}

static inline void ll_crc_set_poly(uint32_t poly) {
    WRITE_REG(CRC->POL, poly);
}

#endif
