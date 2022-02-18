#include "modules.h"
#include "hal_i2c.h"

static const uint8_t hts221_dev_addr = 0xBE;
static const uint8_t hts221_who_am_i_reg = 0x0F;
static const uint8_t hts221_ctrl_reg1_reg = 0x20;

void hts221_simple_test(void) {
    // This Function is only for I2C bring-up testing
    // remove it in future

    uint8_t hts221_rx = 0;
    uint8_t hts221_tx = 0;

    hal_i2c_master_read(I2C2, hts221_dev_addr, hts221_who_am_i_reg, &hts221_rx, 1);
    if (hts221_rx != 0xBC) {
        error_blink();
        return;
    }

    hal_i2c_master_read(I2C2, hts221_dev_addr, hts221_ctrl_reg1_reg, &hts221_rx, 1);
    // Can be on after warm reset
    if ((hts221_rx != 0x00) && (hts221_rx != 0x80)) {
        error_blink();
        return;
    }

    hts221_tx = hts221_rx | 0b10000000;  // Power on
    hal_i2c_master_write(I2C2, hts221_dev_addr, hts221_ctrl_reg1_reg, &hts221_tx, 1);

    hal_i2c_master_read(I2C2, hts221_dev_addr, hts221_ctrl_reg1_reg, &hts221_rx, 1);
    if (hts221_rx != hts221_tx) {
        error_blink();
        return;
    }
}
