#include "hts221.h"

#include <stddef.h>

#include "hal_i2c.h"

hts221_err_t hts221_init(hts221_ctx_t *hts221_ctx, uint8_t device_addres, I2C_TypeDef *I2C) {
    if ((hts221_ctx == NULL) || (I2C == NULL)) {
        return HTS221_ERR_PARAMS;
    }

    hts221_ctx->I2C           = I2C;
    hts221_ctx->device_addres = device_addres;

    return HTS221_NO_ERR;
}

hts221_err_t hts221_read_who_am_i(hts221_ctx_t *hts221_ctx, uint8_t *buffer) {
    if ((hts221_ctx == NULL) || (buffer == NULL)) {
        return HTS221_ERR_PARAMS;
    }

    I2C_TypeDef *I2C = hts221_ctx->I2C;
    uint8_t dev_addr = hts221_ctx->device_addres;
    hal_err_t err    = HAL_NO_ERR;

    err = hal_i2c_master_read(I2C, dev_addr, HTS221_REG_WHO_AM_I, buffer, sizeof(*buffer));
    if (err != HAL_NO_ERR) {
        return HTS221_ERR_COMMUNICATION;
    }

    return HTS221_NO_ERR;
}

hts221_err_t hts221_set_ctrl_reg1(const hts221_ctx_t *hts221_ctx, uint8_t buffer) {
    if ((hts221_ctx == NULL)) {
        return HTS221_ERR_PARAMS;
    }

    uint8_t reserved_mask = 0b10000111;
    buffer &= reserved_mask;

    I2C_TypeDef *I2C = hts221_ctx->I2C;
    uint8_t dev_addr = hts221_ctx->device_addres;
    hal_err_t err    = HAL_NO_ERR;

    err = hal_i2c_master_write(I2C, dev_addr, HTS221_CTRL_REG1, &buffer, sizeof(buffer));
    if (err != HAL_NO_ERR) {
        return HTS221_ERR_COMMUNICATION;
    }

    return HTS221_NO_ERR;
}

hts221_err_t hts221_read_ctrl_reg1(const hts221_ctx_t *hts221_ctx, uint8_t *buffer) {
    if ((hts221_ctx == NULL) || (buffer == NULL)) {
        return HTS221_ERR_PARAMS;
    }

    *buffer = 0x0; // Clear out the buffer

    I2C_TypeDef *I2C = hts221_ctx->I2C;
    uint8_t dev_addr = hts221_ctx->device_addres;
    hal_err_t err    = HAL_NO_ERR;

    err = hal_i2c_master_read(I2C, dev_addr, HTS221_CTRL_REG1, buffer, sizeof(*buffer));
    if (err != HAL_NO_ERR) {
        return HTS221_ERR_COMMUNICATION;
    }

    return HTS221_NO_ERR;
}
