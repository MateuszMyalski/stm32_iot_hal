#include "sdk_i2c.h"

void sdk_i2c_enable_AHB(I2C_TypeDef *I2C) {
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
            break;
    }
}

void sdk_i2c_disable_AHB(I2C_TypeDef *I2C) {
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
            break;
    }
}

// Based on table 539 from reference note
static uint32_t TIMINGR_8Mhz_lut[4][5] = {
    {1U, 0xC7U, 0xC3U, 0x2U, 0x4U},  // I2C 10kHz
    {1U, 0x13U, 0xFU, 0x2U, 0x4U},   // I2C 100kHz
    {0U, 0x9U, 0x3U, 0x1U, 0x3U},    // I2C 400kHz
    {0U, 0x6U, 0x3U, 0x0U, 0x1U}     // I2C 1MHz
};

// Based on table 540 from reference note
static uint32_t TIMINGR_16Mhz_lut[4][5] = {
    {3U, 0xC7U, 0xC3U, 0x2U, 0x4U},  // I2C 10kHz
    {3U, 0x13U, 0xFU, 0x2U, 0x4U},   // I2C 100kHz
    {1U, 0x9U, 0x3U, 0x2U, 0x3U},    // I2C 400kHz
    {0U, 0x4U, 0x2U, 0x0U, 0x2U}     // I2C 1MHz
};

void sdk_i2c_set_clock(I2C_TypeDef *I2C, uint32_t speed, uint32_t sys_core) {
    int lut_speed_idx = 0;
    switch (speed) {
        case 10000:
            lut_speed_idx = 0;
            break;
        case 100000:
            lut_speed_idx = 1;
            break;
        case 400000:
            lut_speed_idx = 2;
            break;
        default:
            lut_speed_idx = 3;
            break;
    }

    if (16000000 == sys_core) {
        MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_PRESC_Msk, TIMINGR_16Mhz_lut[lut_speed_idx][0] << I2C_TIMINGR_PRESC_Pos);
        MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLL_Msk, TIMINGR_16Mhz_lut[lut_speed_idx][1] << I2C_TIMINGR_SCLL_Pos);
        MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLH_Msk, TIMINGR_16Mhz_lut[lut_speed_idx][2] << I2C_TIMINGR_SCLH_Pos);
        MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SDADEL_Msk, TIMINGR_16Mhz_lut[lut_speed_idx][3] << I2C_TIMINGR_SDADEL_Pos);
        MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLDEL_Msk, TIMINGR_16Mhz_lut[lut_speed_idx][4] << I2C_TIMINGR_SCLDEL_Pos);
    } else if (8000000 == sys_core) {
        MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_PRESC_Msk, TIMINGR_8Mhz_lut[lut_speed_idx][0] << I2C_TIMINGR_PRESC_Pos);
        MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLL_Msk, TIMINGR_8Mhz_lut[lut_speed_idx][1] << I2C_TIMINGR_SCLL_Pos);
        MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLH_Msk, TIMINGR_8Mhz_lut[lut_speed_idx][2] << I2C_TIMINGR_SCLH_Pos);
        MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SDADEL_Msk, TIMINGR_8Mhz_lut[lut_speed_idx][3] << I2C_TIMINGR_SDADEL_Pos);
        MODIFY_REG(I2C->TIMINGR, I2C_TIMINGR_SCLDEL_Msk, TIMINGR_8Mhz_lut[lut_speed_idx][4] << I2C_TIMINGR_SCLDEL_Pos);
    }
}

void sdk_i2c_disable(I2C_TypeDef *I2C) {
    CLEAR_BIT(I2C->CR1, I2C_CR1_PE);
}

void sdk_i2c_enable(I2C_TypeDef *I2C) {
    SET_BIT(I2C->CR1, I2C_CR1_PE);
}

void sdk_i2c_enable_dnf(I2C_TypeDef *I2C) {
    SET_BIT(I2C->CR1, I2C_CR1_ANFOFF);
}

void sdk_i2c_disable_dnf(I2C_TypeDef *I2C) {
    CLEAR_BIT(I2C->CR1, I2C_CR1_ANFOFF);
}

void sdk_i2c_set_dnf(I2C_TypeDef *I2C, uint32_t dnf_level) {
    if(0 == dnf_level) {
        CLEAR_BIT(I2C->CR1, I2C_CR1_ANFOFF);
    } else {
        SET_BIT(I2C->CR1, I2C_CR1_ANFOFF);
        return;
    }

    dnf_level &= 0x000FU; // Max 4-bits
    MODIFY_REG(I2C->CR1, I2C_CR1_DNF, dnf_level << I2C_CR1_DNF_Pos);
}

void sdk_i2c_enable_stretch(I2C_TypeDef *I2C) {
    CLEAR_BIT(I2C->CR1, I2C_CR1_NOSTRETCH);
}

void sdk_i2c_disable_stretch(I2C_TypeDef *I2C) {
    SET_BIT(I2C->CR1, I2C_CR1_NOSTRETCH);
}

bool sdk_i2c_read_nack(I2C_TypeDef *I2C) {
    return READ_BIT(I2C->ISR, I2C_ICR_NACKCF);
}

void sdk_i2c_set_slave_addr(I2C_TypeDef *I2C, uint32_t addr) {
    addr &= 0x07FFU; // Max 10-bits

    if(addr > 0x00FFU) {
        SET_BIT(I2C->CR2, I2C_CR2_ADD10);
    } else {
        CLEAR_BIT(I2C->CR2, I2C_CR2_ADD10);
    }

    MODIFY_REG(I2C->CR2, I2C_CR2_SADD_Msk, addr);
}

void sdk_i2c_set_nbytes(I2C_TypeDef *I2C, uint32_t n_bytes) {
    n_bytes &= 0x00FF; // Max 8-bits (255 value)

    MODIFY_REG(I2C->CR2, I2C_CR2_NBYTES_Msk, n_bytes << I2C_CR2_NBYTES_Pos);
}

void sdk_i2c_use_7bit_addr(I2C_TypeDef *I2C) {
    CLEAR_BIT(I2C->CR2, I2C_CR2_ADD10);
}

void sdk_i2c_use_10bit_addr(I2C_TypeDef *I2C) {
    SET_BIT(I2C->CR2, I2C_CR2_ADD10);
}

void sdk_i2c_enable_autoend(I2C_TypeDef *I2C) {
    SET_BIT(I2C->CR2, I2C_CR2_AUTOEND);
}

void sdk_i2c_disable_autoend(I2C_TypeDef *I2C) {
    CLEAR_BIT(I2C->CR2, I2C_CR2_AUTOEND);
}

void sdk_i2c_set_write_dir(I2C_TypeDef *I2C) {
    CLEAR_BIT(I2C->CR2, I2C_CR2_RD_WRN);
}

void sdk_i2c_set_read_dir(I2C_TypeDef *I2C) {
    SET_BIT(I2C->CR2, I2C_CR2_RD_WRN);
}

void sdk_i2c_send_start(I2C_TypeDef *I2C) {
    SET_BIT(I2C->CR2, I2C_CR2_START);
    while (READ_BIT(I2C->CR2, I2C_CR2_START)) {
        // Wait till start generation ends
    }
}

void sdk_i2c_send_stop(I2C_TypeDef *I2C) {
    SET_BIT(I2C->CR2, I2C_CR2_STOP);
}

bool sdk_i2c_is_tx_reg_empty(I2C_TypeDef *I2C) {
    return READ_BIT(I2C->ISR, I2C_ISR_TXIS);
}

void sdk_i2c_load_tx_reg(I2C_TypeDef *I2C, uint32_t data) {
    data &= 0x00FF; // Max 8-bits

    MODIFY_REG(I2C->TXDR, I2C_TXDR_TXDATA_Msk, data << I2C_TXDR_TXDATA_Pos);
}

bool sdk_i2c_is_rx_reg_full(I2C_TypeDef *I2C) {
    return READ_BIT(I2C->ISR, I2C_ISR_RXNE);
}

uint32_t sdk_i2c_read_rx_reg(I2C_TypeDef *I2C) {
    return READ_BIT(I2C->RXDR, I2C_RXDR_RXDATA) & 0x00FF;
}
