#include "hal_i2c.h"
#include <stdbool.h>
#include "sdk_i2c.h"

extern uint32_t SystemCoreClock;
extern volatile uint32_t SysTick_msTicks;

#define DNF_OFF 0x00UL

// Active pooling to minimalize the buffor time between memory writes
#define MEMORY_WRITE_ACTIVE_POOLING

static int master_mode_set_TIMINGR(I2C_TypeDef *I2C, I2C_speed_t I2C_speed) {
    if ((SystemCoreClock != 16000000) && (SystemCoreClock != 8000000)) {
        return 1;
    }

    switch (I2C_speed) {
        case I2C_speed_10kHz:
            sdk_i2c_set_clock(I2C, 10000, SystemCoreClock);
            break;
        case I2C_speed_100kHz:
            sdk_i2c_set_clock(I2C, 100000, SystemCoreClock);
            break;
        case I2C_speed_400kHz:
            sdk_i2c_set_clock(I2C, 400000, SystemCoreClock);
            break;
        case I2C_speed_1MHz:
            sdk_i2c_set_clock(I2C, 1000000, SystemCoreClock);
            break;
        default:
            return -1;
    }

    return 0;
}

static int i2c_master_mode_init(I2C_TypeDef *I2C, I2C_speed_t I2C_speed) {
    sdk_i2c_disable(I2C);
    sdk_i2c_set_dnf(I2C, 0);  // Noise filter OFF

    int err;
    err = master_mode_set_TIMINGR(I2C, I2C_speed);
    if (0 != err) {
        return err;
    }

    sdk_i2c_enable_stretch(I2C);
    sdk_i2c_enable(I2C);

    return 0;
}

static void i2c_reset_state(I2C_TypeDef *I2C) {
    sdk_i2c_disable(I2C);
    for (int i = 0; i < 3; i++) {
        // When cleared, PE must be kept low for at least 3 APB clock cycles.
        asm("nop");
    }
    sdk_i2c_enable(I2C);
}

int hal_i2c_open(I2C_TypeDef *I2C, I2C_mode_t I2C_mode, I2C_speed_t I2C_speed) {
    if (!IS_I2C_ALL_INSTANCE(I2C)) {
        return -1;
    }

    sdk_i2c_enable_APB(I2C);

    switch (I2C_mode) {
        case I2C_mode_slave:
            return 1;
            break;
        case I2C_mode_master:
            return i2c_master_mode_init(I2C, I2C_speed);
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

    sdk_i2c_disable_APB(I2C);
    sdk_i2c_disable(I2C);

    return 0;
}

static void i2c_send_byte(I2C_TypeDef *I2C, uint8_t byte) {
    while (!sdk_i2c_is_tx_reg_empty(I2C)) {
        // Wait till the buffer is empty
    }
    sdk_i2c_load_tx_reg(I2C, byte);
}

static void i2c_read_byte(I2C_TypeDef *I2C, uint8_t *byte) {
    while (!sdk_i2c_is_rx_reg_full(I2C)) {
        // Wait till data copied to buffer
    }
    *byte = sdk_i2c_read_rx_reg(I2C);
}

int hal_i2c_master_write(I2C_TypeDef *I2C, uint16_t dev_addr, uint8_t reg_addr, const uint8_t *data, size_t len) {
    if ((len > 255) || (len <= 0)) {
        // TODO(Mateusz) Currently more than 255 bytes not supported
        return 1;
    }

    sdk_i2c_set_slave_addr(I2C, dev_addr);
    sdk_i2c_set_nbytes(I2C, len + sizeof(uint8_t));
    sdk_i2c_set_write_dir(I2C);
    sdk_i2c_send_start(I2C);

    if (sdk_i2c_read_nack(I2C)) {
        return -1;
    }

    i2c_send_byte(I2C, reg_addr);
    for (int i = 0; i < len; i++) {
        i2c_send_byte(I2C, data[i]);
    }

    // Stop should be automatically generated after
    // received NACK

    return 0;
}

int hal_i2c_master_read(I2C_TypeDef *I2C, uint16_t dev_addr, uint8_t reg_addr, uint8_t *data, size_t len) {
    if ((len > 255) || (len <= 0)) {
        // TODO(Mateusz) Currently more than 255 bytes not supported
        return 1;
    }

    /* Call the device and setup read register */
    sdk_i2c_set_slave_addr(I2C, dev_addr);
    sdk_i2c_set_nbytes(I2C, sizeof(uint8_t));
    sdk_i2c_set_write_dir(I2C);
    sdk_i2c_send_start(I2C);
    i2c_send_byte(I2C, reg_addr);

    if (sdk_i2c_read_nack(I2C)) {
        return -1;
    }

    /* Read content from device's register */
    sdk_i2c_set_slave_addr(I2C, dev_addr);
    sdk_i2c_set_nbytes(I2C, len);
    sdk_i2c_set_read_dir(I2C);
    sdk_i2c_send_start(I2C);
    for (int i = 0; i < len; i++) {
        i2c_read_byte(I2C, &data[i]);
    }

    // Stop should be automatically generated after
    // received NACK

    return 0;
}

int hal_i2c_memory_read(I2C_TypeDef *I2C, uint16_t dev_addr, uint16_t reg_addr, uint8_t *data, size_t len) {
    if ((len > 255) || (len <= 0)) {
        // TODO(Mateusz) Currently more than 255 bytes not supported
        return 1;
    }

    /* Call the device and setup read register */
    sdk_i2c_set_slave_addr(I2C, dev_addr);
    sdk_i2c_set_nbytes(I2C, sizeof(uint16_t));
    sdk_i2c_set_write_dir(I2C);
    sdk_i2c_send_start(I2C);
    i2c_send_byte(I2C, reg_addr >> 8UL);  // Send MSB
    i2c_send_byte(I2C, reg_addr);         // Send LSB

    if (sdk_i2c_read_nack(I2C)) {
        return -1;
    }

    /* Read content from device's register */
    sdk_i2c_set_slave_addr(I2C, dev_addr);
    sdk_i2c_set_nbytes(I2C, len);
    sdk_i2c_set_read_dir(I2C);
    sdk_i2c_send_start(I2C);
    for (int i = 0; i < len; i++) {
        i2c_read_byte(I2C, &data[i]);
    }

    // Stop should be automatically generated after
    // received NACK

    return 0;
}

int hal_i2c_memory_write(I2C_TypeDef *I2C, uint16_t dev_addr, uint16_t reg_addr, const uint8_t *data, size_t len) {
    if ((len > 255) || (len <= 0)) {
        // TODO(Mateusz) Currently more than 255 bytes not supported
        return 1;
    }

retry:
    sdk_i2c_set_slave_addr(I2C, dev_addr);
    sdk_i2c_set_nbytes(I2C, len + sizeof(uint16_t));
    sdk_i2c_set_write_dir(I2C);
    sdk_i2c_enable_autoend(I2C);
    sdk_i2c_send_start(I2C);

    if (sdk_i2c_read_nack(I2C)) {
#ifdef MEMORY_WRITE_ACTIVE_POOLING
        i2c_reset_state(I2C);
        goto retry;
#else
        return -1;
#endif  // MEMORY_WRITE_ACTIVE_POOLING
    }

    // Perform sequentional write only on one page
    i2c_send_byte(I2C, reg_addr >> 8UL);  // Send MSB
    i2c_send_byte(I2C, reg_addr);         // Send LSB
    for (int i = 0; i < len; i++) {
        i2c_send_byte(I2C, data[i]);
    }

    return 0;
}
