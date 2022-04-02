#include "hal_crc.h"

#include <stddef.h>

#include "ll_crc.h"

hal_err_t hal_crc_open(CRC_TypeDef* ctx) {
    if (NULL == ctx) {
        return HAL_ERR_PARAMS;
    }

    ll_crc_enable_AHB(ctx);
    ll_crc_reset(ctx);

    return HAL_NO_ERR;
}

hal_err_t hal_crc_close(CRC_TypeDef* ctx) {
    if (NULL == ctx) {
        return HAL_ERR_PARAMS;
    }

    ll_crc_disable_AHB(ctx);
    return HAL_NO_ERR;
}

hal_err_t hal_crc_ioctl(CRC_TypeDef* ctx, CRC_ioctl_t cmd, void* args) {
    if (NULL == ctx) {
        return HAL_ERR_PARAMS;
    }

    switch (cmd) {
        case CRC_IOCTL_POLY_SIZE_7BIT:
            ll_crc_set_poly_size_7bit(ctx);
            break;

        case CRC_IOCTL_POLY_SIZE_8BIT:
            ll_crc_set_poly_size_8bit(ctx);
            break;

        case CRC_IOCTL_POLY_SIZE_16BIT:
            ll_crc_set_poly_size_16bit(ctx);
            break;

        case CRC_IOCTL_POLY_SIZE_32BIT:
            ll_crc_set_poly_size_32bit(ctx);
            break;

        case CRC_IOCTL_OUT_REVERSED:
            ll_crc_set_out_reversed(ctx, true);
            break;

        case CRC_IOCTL_OUT_NO_REVERSED:
            ll_crc_set_out_reversed(ctx, false);
            break;

        case CRC_IOCTL_IN_NO_REVERSED:
            ll_crc_in_order_no_change(ctx);
            break;

        case CRC_IOCTL_IN_BYTE_REVERSED:
            ll_crc_in_order_rev_by_byte(ctx);
            break;

        case CRC_IOCTL_IN_HALF_WORD_REVERSED:
            ll_crc_in_order_rev_by_half_word(ctx);
            break;

        case CRC_IOCTL_IN_WORD_REVERSED:
            ll_crc_in_order_rev_by_word(ctx);
            break;

        case CRC_IOCTL_SET_POLY:
            if (NULL == args) {
                return HAL_ERR_PARAMS;
            }
            ll_crc_set_poly(ctx, *(uint32_t*)args);
            break;

        case CRC_IOCTL_INIT_CRC:
            if (NULL == args) {
                return HAL_ERR_PARAMS;
            }
            ll_crc_init_crc(ctx, *(uint32_t*)args);
            break;

        default:
            return HAL_ERR_PARAMS;
            break;
    }

    return HAL_NO_ERR;
}

inline static uint32_t byte_swap32(const uint8_t* in) {
    return in[3] | (in[2] << 8) | (in[1] << 16) | (in[0] << 24);
}

inline static uint32_t align_to_word(const uint8_t* in, int size) {
    uint32_t out = 0x0;
    for (int i = 0; i < size; i++) {
        out |= in[i] << (8 * i);
    }
    return out;
}

hal_err_t hal_crc_write(CRC_TypeDef* ctx, const uint8_t* data_in, size_t size) {
    if ((NULL == data_in) || (size < 0)) {
        return HAL_ERR_PARAMS;
    }

    /* Calculate how many even words contain the array (floor the division) */
    size_t n_words = size / sizeof(uint32_t);

    /* Calculate CRC of even 32bit-words */
    for (size_t i = 0; i < (n_words * sizeof(uint32_t)); i += sizeof(uint32_t)) {
        const uint8_t* aligned_word = data_in + i;
        uint32_t data               = byte_swap32(aligned_word);

        ll_crc_write_data_reg(ctx, data);
    }

    size_t n_bytes = size - (n_words * sizeof(uint32_t));
    if (0 < n_bytes) {
        const uint8_t* not_aligned_word = data_in + n_words * sizeof(uint32_t);
        uint32_t data                   = align_to_word(not_aligned_word, n_bytes);

        ll_crc_write_data_reg(ctx, data);
    }

    return HAL_NO_ERR;
}

hal_err_t hal_crc_read(CRC_TypeDef* ctx, uint32_t* value_out) {
    if ((ctx == NULL) || (value_out == NULL)) {
        return HAL_ERR_PARAMS;
    }

    ll_crc_store_crc(ctx);
    ll_crc_reset(ctx);

    (*value_out) = ll_crc_read_stored_crc(ctx);
    return HAL_NO_ERR;
}
