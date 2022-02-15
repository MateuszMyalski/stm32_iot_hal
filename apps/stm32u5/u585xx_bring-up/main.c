#include <stdlib.h>
#include <string.h>

#include "bsp.h"
#include "delay.h"
#include "hal_gpio.h"
#include "hal_i2c.h"
#include "logger.h"
#include "eeprom.h"
#include "eeprom_map.h"

void error_blink() {
    int blink_rate = 300;
    bool led_status = true;
    for (int i = 0; i < blink_rate; i += 50) {
        led_status = !led_status;
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, led_status);
        delay_ms(blink_rate - i);
    }
}

void hts221_simple_test(void) {
    // This Function is only for I2C bring-up testing
    // remove it in future
    uint8_t hts221_dev_addr = 0xBE;
    uint8_t hts221_who_am_i_reg = 0x0F;
    uint8_t hts221_ctrl_reg1_reg = 0x20;

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

void init_eeprom_partitions(void) {
    int err = 0;

    err = eeprom_erease_partition(&extmem_eeprom, EEPROM_PART_DEVICE_INFO_NAME, 0x00);
    if(err){
        error_blink();
        return;
    }
    delay_ms(BSP_EEPROM_WRITE_DELAY_MS);

    err = eeprom_erease_partition(&extmem_eeprom, EEPROM_PART_CNT_INVALID_BOOT_NAME, 0x00);
    if(err){
        error_blink();
        return;
    }
    delay_ms(BSP_EEPROM_WRITE_DELAY_MS);

    err = eeprom_erease_partition(&extmem_eeprom, EEPROM_PART_BOOT_CONFIG_NAME, 0x00);
    if(err){
        error_blink();
        return;
    }
    delay_ms(BSP_EEPROM_WRITE_DELAY_MS);

    err = eeprom_erease_partition(&extmem_eeprom, EEPROM_PART_BOOT_WIFI_CREDS_A_NAME, 0x00);
    if(err){
        error_blink();
        return;
    }
    delay_ms(BSP_EEPROM_WRITE_DELAY_MS);

    err = eeprom_erease_partition(&extmem_eeprom, EEPROM_PART_BOOT_WIFI_CREDS_B_NAME, 0x00);
    if(err){
        error_blink();
        return;
    }
    delay_ms(BSP_EEPROM_WRITE_DELAY_MS);
}

int main() {
    Assert(bsp_init(), 0);
    // hts221_simple_test();
    // init_eeprom_partitions();

    part_device_info_t device_info = {0xFF};
    int err = 0;
    // err = eeprom_store_partition(&extmem_eeprom, EEPROM_PART_DEVICE_INFO_NAME, (const uint8_t *)&device_info);
    err = eeprom_load_partition(&extmem_eeprom, EEPROM_PART_DEVICE_INFO_NAME, (uint8_t *)&device_info);
    if(err){
        error_blink();
        while(1);
    }


    while (1) {
        bool r_value = !hal_gpio_read(BSP_USER_BUTTON_PORT, BSP_USER_BUTTON_PIN);
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, false);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, r_value);
        delay_ms(500);
        hal_gpio_write(BSP_GREEN_LED_PORT, BSP_GREEN_LED_PIN, true);
        hal_gpio_write(BSP_RED_LED_PORT, BSP_RED_LED_PIN, r_value);
        delay_ms(300);
    }
}
