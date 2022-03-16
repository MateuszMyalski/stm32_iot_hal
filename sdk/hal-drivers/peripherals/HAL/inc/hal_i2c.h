#ifndef HAL_I2C_H
#define HAL_I2C_H
#include <stddef.h>

#include "hal_common.h"

typedef enum { I2C_mode_slave, I2C_mode_master, I2C_mode_SMBUS_master, I2C_mode_SMBUS_slave } I2C_mode_t;

typedef enum { I2C_speed_10kHz, I2C_speed_100kHz, I2C_speed_400kHz, I2C_speed_1MHz } I2C_speed_t;

/**
 * @brief Configure I2C peripherial.
 * @note No GPIO init is performed.
 * @param I2C - CMSIS I2C instance
 * @param I2C_mode - I2C mode enumeration
 * @param I2C_speed - I2C speed enumeration
 * @return HAL Error code. 0 - Success
 */
hal_err_t hal_i2c_open(I2C_TypeDef *I2C, I2C_mode_t I2C_mode, I2C_speed_t I2C_speed);

/**
 * @brief Turn off and reset I2C peripherial.
 * @note No GPIO deinit is performed.
 * @param I2C - CMSIS I2C instance
 * @return HAL Error code. 0 - Success
 */
hal_err_t hal_i2c_close(I2C_TypeDef *I2C);

/**
 * @brief Configure with demanded mode I2C peripherial
 * @param I2C - CMSIS I2C instance
 * @return HAL Error code. 0 - Success
 */
hal_err_t hal_i2c_ioctl(I2C_TypeDef *I2C);

/**
 * @brief Perform I2C master read.
 * @note START | DEV_ADDR [W]| A | CELL_ADDR | A | START | DEV_ADDR [R] | A | DATA (x len) | NACK | STOP
 * @param I2C - CMSIS I2C instance
 * @param dev_addr - Slave device address
 * @param mem_addr - Slave's cell address
 * @param data - Read data buffer
 * @param size - Read data buffer length (in bytes)
 * @return HAL Error code. 0 - Success
 */
hal_err_t hal_i2c_master_read(I2C_TypeDef *I2C, uint16_t dev_addr, uint8_t mem_addr, uint8_t *data, size_t size);

/**
 * @brief Perform I2C master write.
 * @note START | DEV_ADDR [W]| A | CELL_ADDR | DATA (x len) | NACK | STOP
 * @param I2C - CMSIS I2C instance
 * @param dev_addr - Slave device address
 * @param mem_addr - Slave's cell address
 * @param data - Write data buffer
 * @param size - Write data buffer length (in bytes)
 * @return HAL Error code. 0 - Success
 */
hal_err_t hal_i2c_master_write(I2C_TypeDef *I2C, uint16_t dev_addr, uint8_t mem_addr, const uint8_t *data, size_t size);

#endif
