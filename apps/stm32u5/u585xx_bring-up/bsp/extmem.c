#include "eeprom.h"
#include "bsp.h"
#include "hal_i2c.h"
#include "eeprom_map.h"

eeprom_t extmem_eeprom = {.device = NO_DEVICE};
partition_entry_t eeprom_part_table[] = {
    {
        DEVICE_INFO_NAME,
        0x0U,
        DEVICE_INFO_BEGIN,
        DEVICE_INFO_END,
        DEVICE_INFO_LEN
    },
    {
        CNT_INVALID_BOOT_A_NAME,
        0x0U,
        CNT_INVALID_BOOT_A_BEGIN,
        CNT_INVALID_BOOT_A_END,
        CNT_INVALID_BOOT_A_LEN
    },
    {
        CNT_INVALID_BOOT_B_NAME,
        0x0U,
        CNT_INVALID_BOOT_B_BEGIN,
        CNT_INVALID_BOOT_B_END,
        CNT_INVALID_BOOT_B_LEN
    },
    {
        BOOT_CONFIG_NAME,
        0x0U,
        BOOT_CONFIG_BEGIN,
        BOOT_CONFIG_END,
        BOOT_CONFIG_LEN
    },
    {
        BOOT_WIFI_CREDS_A_NAME,
        0x0U,
        BOOT_WIFI_CREDS_A_BEGIN,
        BOOT_WIFI_CREDS_A_END,
        BOOT_WIFI_CREDS_A_LEN
    },
    {
        BOOT_WIFI_CREDS_B_NAME,
        0x0U,
        BOOT_WIFI_CREDS_B_BEGIN,
        BOOT_WIFI_CREDS_B_END,
        BOOT_WIFI_CREDS_B_LEN
    }
};


static int eeprom_tx_data(uint16_t mem_addr, const uint8_t *data, size_t len) {
    int err = 0;
    err = hal_i2c_memory_write(BSP_EEPROM_I2C, BSP_EEPROM_ADDR, mem_addr, data, len);

    return err;
}

static int eeprom_rx_data(uint16_t mem_addr, uint8_t *data, size_t len) {
    int err = 0;
    err = hal_i2c_memory_read(BSP_EEPROM_I2C, BSP_EEPROM_ADDR, mem_addr, data, len);

    return err;
}

int bsp_init_eeprom(void) {
    extmem_eeprom.device = M24256_D;
    extmem_eeprom.page_size = EEPROM_PAGE_SIZE;
    extmem_eeprom.memory_size = EEPROM_SIZE;
    extmem_eeprom.tx_data_cb = &eeprom_tx_data;
    extmem_eeprom.rx_data_cb = &eeprom_rx_data;

    return 0;
}
