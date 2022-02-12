#ifndef SDK_I2C_H
#define SDK_I2C_H
#include <stdbool.h>
#include "stm32u585xx.h"
#include "stm32u5xx.h"

void sdk_i2c_enable_AHB(I2C_TypeDef *I2C);
void sdk_i2c_disable_AHB(I2C_TypeDef *I2C);

void sdk_i2c_set_clock(I2C_TypeDef *I2C, uint32_t speed, uint32_t sys_core);

void sdk_i2c_disable(I2C_TypeDef *I2C);
void sdk_i2c_enable(I2C_TypeDef *I2C);

void sdk_i2c_enable_dnf(I2C_TypeDef *I2C);
void sdk_i2c_disable_dnf(I2C_TypeDef *I2C);
void sdk_i2c_set_dnf(I2C_TypeDef *I2C, uint32_t dnf_level);

void sdk_i2c_enable_stretch(I2C_TypeDef *I2C);
void sdk_i2c_disable_stretch(I2C_TypeDef *I2C);

bool sdk_i2c_read_nack(I2C_TypeDef *I2C);

void sdk_i2c_set_slave_addr(I2C_TypeDef *I2C, uint32_t addr);
void sdk_i2c_set_nbytes(I2C_TypeDef *I2C, uint32_t n_bytes);

void sdk_i2c_use_7bit_addr(I2C_TypeDef *I2C);
void sdk_i2c_use_10bit_addr(I2C_TypeDef *I2C);

void sdk_i2c_enable_autoend(I2C_TypeDef *I2C);
void sdk_i2c_disable_autoend(I2C_TypeDef *I2C);

void sdk_i2c_set_write_dir(I2C_TypeDef *I2C);
void sdk_i2c_set_read_dir(I2C_TypeDef *I2C);

void sdk_i2c_send_start(I2C_TypeDef *I2C);
void sdk_i2c_send_stop(I2C_TypeDef *I2C);

bool sdk_i2c_is_tx_reg_empty(I2C_TypeDef *I2C);
void sdk_i2c_load_tx_reg(I2C_TypeDef *I2C, uint32_t data);

bool sdk_i2c_is_rx_reg_full(I2C_TypeDef *I2C);
uint32_t sdk_i2c_read_rx_reg(I2C_TypeDef *I2C);

#endif
