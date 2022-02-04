#ifndef I2C_H
#define I2C_H
#include <stddef.h>
#include "hal_common.h"

typedef enum { I2C_mode_slave, I2C_mode_master, I2C_mode_SMBUS_master, I2C_mode_SMBUS_slave } I2C_mode_t;

typedef enum { I2C_speed_10kHz, I2C_speed_100kHz, I2C_speed_400kHz, I2C_speed_1MHz } I2C_speed_t;

int hal_i2c_open(I2C_TypeDef *I2C, I2C_mode_t I2C_mode);
int hal_i2c_close(I2C_TypeDef *I2C);

int hal_i2c_ioctl(I2C_TypeDef *I2C);

int hal_i2c_master_read(I2C_TypeDef *I2C, uint16_t dev_addr, uint8_t mem_addr, uint8_t *data, size_t len);
int hal_i2c_master_write(I2C_TypeDef *I2C, uint16_t dev_addr, const uint8_t *data, size_t len);

#endif
