#ifndef DEVICES_HTS221_H
#define DEVICES_HTS221_H

#include <stdint.h>

#include "hal_common.h"

#define HTS221_REG_WHO_AM_I 0x0FUL
#define HTS221_CTRL_REG1    0x20UL

typedef enum {
    HTS221_NO_ERR            = 0,
    HTS221_ERR_INIT          = -1,
    HTS221_ERR_PARAMS        = -2,
    HTS221_ERR_COMMUNICATION = -3
} hts221_err_t;

typedef enum {
    HTS221_CTRL_REG1_PD   = (1UL << 7UL),
    HTS221_CTRL_REG1_BDU  = (1UL << 2UL),
    HTS221_CTRL_REG1_ODR1 = (1UL << 1UL),
    HTS221_CTRL_REG1_ODR0 = 1UL
} hts_221_ctrl_reg1_t;

typedef struct {
    uint8_t device_addres;
    I2C_TypeDef *I2C;
} hts221_ctx_t;

/**
 * @brief Initialize HTS221 device
 * @param hts221_ctx - Device structure context
 * @param device_addres - I2C device address
 * @param I2C - CMSIS I2C initialized context
 * @return HTS221 Error code. 0 - Success
 */
hts221_err_t hts221_init(hts221_ctx_t *hts221_ctx, uint8_t device_addres, I2C_TypeDef *I2C);

/**
 * @brief Reads the device who am I register
 * @param hts221_ctx - Device structure context
 * @param buffer - Read data
 * @return HTS221 Error code. 0 - Success
 */
hts221_err_t hts221_read_who_am_i(hts221_ctx_t *hts221_ctx, uint8_t *buffer);

/**
 * @brief Set the control register 1
 * @param hts221_ctx - Device structure context
 * @param buffer - Data to write
 * @return HTS221 Error code. 0 - Success
 */
hts221_err_t hts221_set_ctrl_reg1(const hts221_ctx_t *hts221_ctx, uint8_t buffer);

/**
 * @brief Set the control register 1
 * @param hts221_ctx - Device structure context
 * @param buffer - Read data
 * @return HTS221 Error code. 0 - Success
 */
hts221_err_t hts221_read_ctrl_reg1(const hts221_ctx_t *hts221_ctx, uint8_t *buffer);

#endif
