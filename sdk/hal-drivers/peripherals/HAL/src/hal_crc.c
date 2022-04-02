#include "hal_crc.h"

#include <stddef.h>

#include "ll_crc.h"

hal_err_t hal_crc_open() {
    ll_crc_enable_AHB();
    ll_crc_reset();
    return HAL_NO_ERR;
}

hal_err_t hal_crc_close() {
    ll_crc_disable_AHB();
    return HAL_NO_ERR;
}

hal_err_t hal_crc_ioctl(CRC_ioctl_t CRC_ioctl) {
    switch (CRC_ioctl) {
        case CRC_ioctl_poly_size_7bit:
            ll_crc_set_poly_size_7bit();
            break;

        case CRC_ioctl_poly_size_8bit:
            ll_crc_set_poly_size_8bit();
            break;

        case CRC_ioctl_poly_size_16bit:
            ll_crc_set_poly_size_16bit();
            break;

        case CRC_ioctl_poly_size_32bit:
            ll_crc_set_poly_size_32bit();
            break;

        case CRC_ioctl_out_reversed:
            ll_crc_set_out_reversed(true);
            break;

        case CRC_ioctl_out_no_reversed:
            ll_crc_set_out_reversed(false);
            break;

        case CRC_ioctl_in_no_reversed:
            ll_crc_in_order_no_change();
            break;

        case CRC_ioctl_in_byte_reversed:
            ll_crc_in_order_rev_by_byte();
            break;

        case CRC_ioctl_in_half_word_reversed:
            ll_crc_in_order_rev_by_half_word();
            break;

        case CRC_ioctl_in_word_reversed:
            ll_crc_in_order_rev_by_word();
            break;

        case CRC_ioctl_poly_crc16citt:
            ll_crc_set_poly(0x1021);
            break;

        case CRC_ioctl_poly_crc16ibm:
            ll_crc_set_poly(0x8005);
            break;

        case CRC_ioctl_poly_crc16t10dif:
            ll_crc_set_poly(0x8BB7);
            break;

        case CRC_ioctl_poly_crc16dnp:
            ll_crc_set_poly(0x3D65);
            break;

        case CRC_ioctl_poly_crc16dect:
            ll_crc_set_poly(0x0589);
            break;

        case CRC_ioctl_poly_crc32:
            ll_crc_set_poly(0x04C11DB7);
            break;

        case CRC_ioctl_poly_crc32c:
            ll_crc_set_poly(0x1EDC6F41);
            break;

        case CRC_ioctl_poly_crc32k:
            ll_crc_set_poly(0x741B8CD7);
            break;

        case CRC_ioctl_poly_crc32q:
            ll_crc_set_poly(0x814141AB);
            break;

        default:
            return HAL_ERR_PARAMS;
            break;
    }
    return HAL_ERR_PARAMS;
}

hal_err_t hal_crc_write(const uint8_t* data_in, size_t size) {
    if ((NULL == data_in) || (size < 0)) {
        return HAL_ERR_PARAMS;
    }

    size_t n_words = size / sizeof(uint32_t);
    for (size_t i = 0; i < n_words; i++) {
        uint8_t* v4  = data_in + i * sizeof(uint32_t);
        uint32_t i32 = v4[3] | (v4[2] << 8) | (v4[1] << 16) | (v4[0] << 24);
        ll_crc_write_data_reg(i32);
    }

    size_t n_bytes = size - (n_words * sizeof(uint32_t));
    if (0 < n_bytes) {
        uint32_t i32 = 0x0;
        uint8_t* v4  = data_in + n_words * sizeof(uint32_t);
        for (size_t i = 0; i < n_bytes; i++) {
            i32 |= v4[i] << (8 * i);
        }
        ll_crc_write_data_reg(i32);
    }

    return HAL_NO_ERR;
}

hal_err_t hal_crc_read(uint32_t* value_out) {
    if (value_out == NULL) {
        return HAL_ERR_PARAMS;
    }

    ll_crc_store_crc();
    ll_crc_reset();

    (*value_out) = ll_crc_read_stored_crc();
    return HAL_NO_ERR;
}

hal_err_t hal_crc_poly_init(uint32_t data) {
    ll_crc_init_crc(data);
    return HAL_NO_ERR;
}
