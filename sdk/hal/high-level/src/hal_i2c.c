#include "hal_i2c.h"

#include <stdbool.h>

#include "ll_i2c.h"

extern uint32_t SystemCoreClock;
extern volatile uint32_t SysTick_msTicks;

#define DNF_OFF 0x00UL

// Active pooling to minimalize the buffor time between memory writes
#define MEMORY_WRITE_ACTIVE_POOLING

static int master_mode_set_TIMINGR(I2C_TypeDef *I2C, I2C_speed_t I2C_speed) {
    if ((SystemCoreClock != 16000000) && (SystemCoreClock != 8000000)) {
        return HAL_ERR_NOT_IMPLEMENTED;
    }

    switch (I2C_speed) {
        case I2C_speed_10kHz:
            ll_i2c_set_clock(I2C, 10000, SystemCoreClock);
            break;
        case I2C_speed_100kHz:
            ll_i2c_set_clock(I2C, 100000, SystemCoreClock);
            break;
        case I2C_speed_400kHz:
            ll_i2c_set_clock(I2C, 400000, SystemCoreClock);
            break;
        case I2C_speed_1MHz:
            ll_i2c_set_clock(I2C, 1000000, SystemCoreClock);
            break;
        default:
            return HAL_ERR_PARAMS;
    }

    return HAL_NO_ERR;
}

static int i2c_master_mode_init(I2C_TypeDef *I2C, I2C_speed_t I2C_speed) {
    ll_i2c_disable(I2C);
    ll_i2c_set_dnf(I2C, 0);  // Noise filter OFF

    int err;
    err = master_mode_set_TIMINGR(I2C, I2C_speed);
    if (0 != err) {
        return err;
    }

    ll_i2c_enable_stretch(I2C);
    ll_i2c_enable(I2C);

    return HAL_NO_ERR;
}

hal_err_t hal_i2c_open(I2C_TypeDef *I2C, I2C_mode_t I2C_mode, I2C_speed_t I2C_speed) {
    if (!IS_I2C_ALL_INSTANCE(I2C)) {
        return -1;
    }

    ll_i2c_enable_APB(I2C);

    switch (I2C_mode) {
        case I2C_mode_slave:
            return HAL_ERR_NOT_IMPLEMENTED;
            break;
        case I2C_mode_master:
            return i2c_master_mode_init(I2C, I2C_speed);
        case I2C_mode_SMBUS_master:
            return HAL_ERR_NOT_IMPLEMENTED;
            break;
        case I2C_mode_SMBUS_slave:
            return HAL_ERR_NOT_IMPLEMENTED;
            break;
    }

    return HAL_NO_ERR;
}

hal_err_t hal_i2c_close(I2C_TypeDef *I2C) {
    if (!IS_I2C_ALL_INSTANCE(I2C)) {
        return HAL_ERR_PARAMS;
    }

    ll_i2c_disable_APB(I2C);
    ll_i2c_disable(I2C);

    return HAL_NO_ERR;
}

hal_err_t hal_i2c_master_write(I2C_TypeDef *I2C, uint16_t dev_addr, uint8_t mem_addr, const uint8_t *data, size_t size) {
    if ((size > 255) || (size <= 0)) {
        // TODO(Mateusz) Currently more than 255 bytes not supported
        return HAL_ERR_NOT_IMPLEMENTED;
    }

    ll_i2c_set_slave_addr(I2C, dev_addr);
    ll_i2c_set_nbytes(I2C, size + sizeof(uint8_t));
    ll_i2c_set_write_dir(I2C);
    ll_i2c_send_start(I2C);

    if (ll_i2c_read_nack(I2C)) {
        return -1;
    }

    ll_i2c_send_byte(I2C, mem_addr);
    for (int i = 0; i < size; i++) {
        ll_i2c_send_byte(I2C, data[i]);
    }

    // Stop should be automatically generated after
    // received NACK

    return HAL_NO_ERR;
}

hal_err_t hal_i2c_master_read(I2C_TypeDef *I2C, uint16_t dev_addr, uint8_t mem_addr, uint8_t *data, size_t size) {
    if ((size > 255) || (size <= 0)) {
        // TODO(Mateusz) Currently more than 255 bytes not supported
        return HAL_ERR_NOT_IMPLEMENTED;
    }

    /* Call the device and setup read register */
    ll_i2c_set_slave_addr(I2C, dev_addr);
    ll_i2c_set_nbytes(I2C, sizeof(uint8_t));
    ll_i2c_set_write_dir(I2C);
    ll_i2c_send_start(I2C);
    ll_i2c_send_byte(I2C, mem_addr);

    if (ll_i2c_read_nack(I2C)) {
        return -1;
    }

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

    return HAL_NO_ERR;
}
