#include "i2c.h"
#include <stdbool.h>

extern uint32_t SystemCoreClock;
extern volatile uint32_t SysTick_msTicks;

#define DNF_OFF 0x00UL

static int master_mode_set_TIMINGR(I2C_TypeDef *I2C, I2C_speed_t I2C_speed) {
    if (SystemCoreClock != 16000000) {
        // Assume I2CCLK = 16MHz
        // TODO(Mateusz) add 8MHz version
        return 1;
    }

    // Based on table 540 from reference note
    switch (I2C_speed) {
        case I2C_speed_10kHz:
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_PRESC_Msk, 3U << I2C_TIMINGR_PRESC_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLL_Msk, 0xC7U << I2C_TIMINGR_SCLL_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLH_Msk, 0xC3U << I2C_TIMINGR_SCLH_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SDADEL_Msk, 0x2U << I2C_TIMINGR_SDADEL_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLDEL_Msk, 0x4U << I2C_TIMINGR_SCLDEL_Pos);
            break;
        case I2C_speed_100kHz:
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_PRESC_Msk, 3U << I2C_TIMINGR_PRESC_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLL_Msk, 0x13U << I2C_TIMINGR_SCLL_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLH_Msk, 0xFU << I2C_TIMINGR_SCLH_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SDADEL_Msk, 0x2U << I2C_TIMINGR_SDADEL_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLDEL_Msk, 0x4U << I2C_TIMINGR_SCLDEL_Pos);
            break;
        case I2C_speed_400kHz:
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_PRESC_Msk, 1U << I2C_TIMINGR_PRESC_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLL_Msk, 0x9U << I2C_TIMINGR_SCLL_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLH_Msk, 0x3U << I2C_TIMINGR_SCLH_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SDADEL_Msk, 0x2U << I2C_TIMINGR_SDADEL_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLDEL_Msk, 0x3U << I2C_TIMINGR_SCLDEL_Pos);
            break;
        case I2C_speed_1MHz:
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_PRESC_Msk, 0U << I2C_TIMINGR_PRESC_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLL_Msk, 0x4U << I2C_TIMINGR_SCLL_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLH_Msk, 0x2U << I2C_TIMINGR_SCLH_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SDADEL_Msk, 0x0U << I2C_TIMINGR_SDADEL_Pos);
            MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLDEL_Msk, 0x2U << I2C_TIMINGR_SCLDEL_Pos);
            break;
        default:
            return -1;
            break;
    }

    return 0;
}

static int i2c_master_mode_init(I2C_TypeDef *I2C) {
    /* Clear PE bit in Initialize I2C_CR1 */
    CLEAR_BIT(I2C->CR1, I2C_CR1_PE);

    /* Configure ANFOFF and DNF bits */
    // Noise filter OFF
    CLEAR_BIT(I2C->CR1, I2C_CR1_ANFOFF);
    MODIFY_REG(I2C->CR1, I2C_CR1_DNF, DNF_OFF);

    /* Configure I2C_TIMINGR */
    int err;
    err = master_mode_set_TIMINGR(I2C, I2C_speed_100kHz);
    if (0 != err) {
        return err;
    }

    /* Configure NOSTRETCH in I2C_CR1 */
    CLEAR_BIT(I2C->CR1, I2C_CR1_NOSTRETCH);

    /* Set PE bit in I2C_CR1 */
    SET_BIT(I2C->CR1, I2C_CR1_PE);

    return 0;
}

int hal_i2c_open(I2C_TypeDef *I2C, I2C_mode_t I2C_mode) {
    if (!IS_I2C_ALL_INSTANCE(I2C)) {
        return -1;
    }

    // Enable AHB bus
    switch ((intptr_t)I2C) {
        case I2C1_BASE:
            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN);
            break;
        case I2C2_BASE:
            SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN);
            break;
        case I2C3_BASE:
            SET_BIT(RCC->APB3ENR, RCC_APB3ENR_I2C3EN);
            break;
        case I2C4_BASE:
            SET_BIT(RCC->APB1ENR2, RCC_APB1ENR2_I2C4EN);
            break;
        default:
            return -1;
            break;
    }

    switch (I2C_mode) {
        case I2C_mode_slave:
            return 1;
            break;
        case I2C_mode_master:
            return i2c_master_mode_init(I2C);
            break;
        case I2C_mode_SMBUS_master:
            return 1;
            break;
        case I2C_mode_SMBUS_slave:
            return 1;
            break;
    }

    return 0;
}

int hal_i2c_close(I2C_TypeDef *I2C) {
    if (!IS_I2C_ALL_INSTANCE(I2C)) {
        return -1;
    }

    // Reset AHB bus
    switch ((intptr_t)I2C) {
        case I2C1_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C1RST);
            break;
        case I2C2_BASE:
            SET_BIT(RCC->APB1RSTR1, RCC_APB1RSTR1_I2C2RST);
            break;
        case I2C3_BASE:
            SET_BIT(RCC->APB3RSTR, RCC_APB3RSTR_I2C3RST);
            break;
        case I2C4_BASE:
            SET_BIT(RCC->APB1RSTR2, RCC_APB1RSTR2_I2C4RST);
            break;
        default:
            return -1;
            break;
    }

    // Software reset
    CLEAR_BIT(I2C->CR1, I2C_CR1_PE);

    return 0;
}

static void i2c_start(I2C_TypeDef *I2C) {
    SET_BIT(I2C->CR2, I2C_CR2_START);
    while (READ_BIT(I2C->CR2, I2C_CR2_START)) {
        // Wait till start generation ends
    }
}

static void i2c_stop(I2C_TypeDef *I2C) { SET_BIT(I2C->CR2, I2C_CR2_STOP); }

static void i2c_send_byte(I2C_TypeDef *I2C, uint8_t byte) {
    while (!READ_BIT(I2C->ISR, I2C_ISR_TXIS)) {
        // Wait till the buffer is empty
    }
    MODIFY_REG(I2C->TXDR, I2C_TXDR_TXDATA_Msk, byte << I2C_TXDR_TXDATA_Pos);
}

static void i2c_set_nbytes_devaddr(I2C_TypeDef *I2C, size_t len, uint16_t dev_addr) {
    if (dev_addr > 0x00FFU) {
        SET_BIT(I2C->CR2, I2C_CR2_ADD10);
    } else {
        CLEAR_BIT(I2C->CR2, I2C_CR2_ADD10);
    }

    MODIFY_REG(I2C->CR2, I2C_CR2_SADD_Msk, dev_addr);
    MODIFY_REG(I2C->CR2, I2C_CR2_NBYTES_Msk, len << I2C_CR2_NBYTES_Pos);
}

static void i2c_set_read_dir(I2C_TypeDef *I2C, bool set_read) {
    if (set_read) {
        SET_BIT(I2C->CR2, I2C_CR2_RD_WRN);
    } else {
        CLEAR_BIT(I2C->CR2, I2C_CR2_RD_WRN);
    }
}

static void i2c_read_byte(I2C_TypeDef *I2C, uint8_t *byte) {
    while (!READ_BIT(I2C->ISR, I2C_ISR_RXNE)) {
        // Wait till data copied to buffer
    }
    *byte = I2C->RXDR & I2C_RXDR_RXDATA_Msk;
}

int hal_i2c_master_write(I2C_TypeDef *I2C, uint16_t dev_addr, const uint8_t *data, size_t len) {
    if ((len > 255) || (len <= 0)) {
        // TODO(Mateusz) Currently more than 255 bytes not supported
        return 1;
    }

    i2c_set_nbytes_devaddr(I2C, len, dev_addr);

    i2c_set_read_dir(I2C, false);

    i2c_start(I2C);

    for (int i = 0; i < len; i++) {
        i2c_send_byte(I2C, data[i]);
    }

    i2c_stop(I2C);

    return 0;
}

int hal_i2c_master_read(I2C_TypeDef *I2C, uint16_t dev_addr, uint8_t mem_addr, uint8_t *data, size_t len) {
    if (len > 255) {
        // TODO(Mateusz) Currently more than 255 bytes not supported
        return 1;
    }

    /* Call the device and setup read register */
    i2c_set_nbytes_devaddr(I2C, 1, dev_addr);
    // SET_BIT(I2C->CR2, I2C_CR2_AUTOEND);
    i2c_set_read_dir(I2C, false);
    i2c_start(I2C);
    i2c_send_byte(I2C, mem_addr);

    /* Read content from device's register */
    i2c_set_nbytes_devaddr(I2C, len, dev_addr);
    i2c_set_read_dir(I2C, true);
    i2c_start(I2C);
    for (int i = 0; i < len; i++) {
        i2c_read_byte(I2C, &data[i]);
    }

    i2c_stop(I2C);

    return 0;
}
