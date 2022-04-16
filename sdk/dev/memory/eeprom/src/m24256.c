#include "m24256.h"

#include "ll_i2c.h"

eeprom_err_t m24256_init(eeprom_ctx_t *eeprom_ctx, uint8_t device_address, I2C_TypeDef *I2C,
                         const uint32_t *ms_tick_source) {
    if ((NULL == eeprom_ctx) || (NULL == I2C)) {
        return EEPROM_ERR_PARAMS;
    }

    eeprom_ctx->device_address = device_address;
    eeprom_ctx->I2C            = I2C;
    eeprom_ctx->ms_tick_source = ms_tick_source;

    return EEPROM_NO_ERR;
}

eeprom_err_t m24256_write(eeprom_ctx_t *eeprom_ctx, uint16_t mem_addr, const uint8_t *data, size_t size) {
    if ((NULL == eeprom_ctx) || (NULL == data)) {
        return EEPROM_ERR_PARAMS;
    }

    if ((size > 255) || (size <= 0)) {
        // TODO(Mateusz) Currently more than 255 bytes not supported
        return HAL_ERR_NOT_IMPLEMENTED;
    }

    I2C_TypeDef *I2C = eeprom_ctx->I2C;
    uint8_t dev_addr = eeprom_ctx->device_address;
    bool no_timeout  = (NULL == eeprom_ctx->ms_tick_source) || (0 == eeprom_ctx->timeout);

    uint32_t timeout_time = 0;
    if (!no_timeout) {
        timeout_time = *eeprom_ctx->ms_tick_source + eeprom_ctx->timeout;
    }

retry:
    ll_i2c_set_slave_addr(I2C, dev_addr);
    ll_i2c_set_nbytes(I2C, size + sizeof(uint16_t));
    ll_i2c_set_write_dir(I2C);
    ll_i2c_enable_autoend(I2C);
    ll_i2c_send_start(I2C);

    if (ll_i2c_read_nack(I2C)) {
        ll_i2c_reset(I2C);

        // Active polling to not use delays between r/w cycles
        if (!no_timeout && (timeout_time > *eeprom_ctx->ms_tick_source)) {
            goto retry;
        } else {
            return no_timeout ? EEPROM_ERR_WRITE : EEPROM_ERR_TIMEOUT;
        }
    }

    // Perform sequentional write only on one page
    ll_i2c_send_byte(I2C, mem_addr >> 8UL);  // Send MSB
    ll_i2c_send_byte(I2C, mem_addr);         // Send LSB
    for (int i = 0; i < size; i++) {
        ll_i2c_send_byte(I2C, data[i]);
    }

    return EEPROM_NO_ERR;
}

eeprom_err_t m24256_read(eeprom_ctx_t *eeprom_ctx, uint16_t mem_addr, uint8_t *data, size_t size) {
    if ((NULL == eeprom_ctx) || (NULL == data)) {
        return EEPROM_ERR_PARAMS;
    }

    if ((size > 255) || (size <= 0)) {
        // TODO(Mateusz) Currently more than 255 bytes not supported
        return HAL_ERR_NOT_IMPLEMENTED;
    }

    I2C_TypeDef *I2C = eeprom_ctx->I2C;
    uint8_t dev_addr = eeprom_ctx->device_address;
    bool no_timeout  = (NULL == eeprom_ctx->ms_tick_source) || (0 == eeprom_ctx->timeout);

    uint32_t timeout_time = 0;
    if (!no_timeout) {
        timeout_time = *eeprom_ctx->ms_tick_source + eeprom_ctx->timeout;
    }

retry:
    /* Call the device and setup read register */
    ll_i2c_set_slave_addr(I2C, dev_addr);
    ll_i2c_set_nbytes(I2C, sizeof(uint16_t));
    ll_i2c_set_write_dir(I2C);
    ll_i2c_send_start(I2C);

    if (ll_i2c_read_nack(I2C)) {
        // Active polling to not use delays between r/w cycles
        if (!no_timeout && (timeout_time > *eeprom_ctx->ms_tick_source)) {
            goto retry;
        } else {
            return no_timeout ? EEPROM_ERR_READ : EEPROM_ERR_TIMEOUT;
        }
    }

    /* Send register address */
    ll_i2c_send_byte(I2C, mem_addr >> 8UL);  // Send MSB
    ll_i2c_send_byte(I2C, mem_addr);         // Send LSB

    /* Read content from device's register */
    ll_i2c_set_slave_addr(I2C, dev_addr);
    ll_i2c_set_nbytes(I2C, size);
    ll_i2c_set_read_dir(I2C);
    ll_i2c_send_start(I2C);
    for (int i = 0; i < size; i++) {
        ll_i2c_read_byte(I2C, &data[i]);
    }

    // Stop should be automatically generated after
    // received NACK

    return EEPROM_NO_ERR;
}

eeprom_err_t m24256_set_timeout(eeprom_ctx_t *eeprom_ctx, uint32_t timeout_ms) {
    if ((NULL == eeprom_ctx) || (NULL == eeprom_ctx->ms_tick_source)) {
        return EEPROM_ERR_PARAMS;
    }
    eeprom_ctx->timeout = timeout_ms;

    return EEPROM_NO_ERR;
}
