#include "eeprom.h"
#include "bsp.h"
#include "hal_i2c.h"
#include "eeprom_map.h"

eeprom_t extmem_eeprom = {.device = NO_DEVICE};
partition_entry_t eeprom_part_table[] = {
    {
        EEPROM_PART_DEVICE_INFO_NAME,
        EEPROM_PART_DEVICE_INFO_MAGIC,
        EEPROM_PART_MAGIC_SIZE,
        PARTITION_FLAG_USE_CRC,
        EEPROM_PART_DEVICE_INFO_BEGIN,
        EEPROM_PART_DEVICE_INFO_END,
        EEPROM_PART_DEVICE_INFO_SIZE
    },
    {
        EEPROM_PART_CNT_INVALID_BOOT_NAME,
        EEPROM_PART_CNT_INVALID_BOOT_MAGIC,
        EEPROM_PART_MAGIC_SIZE,
        0x0U,
        EEPROM_PART_CNT_INVALID_BOOT_BEGIN,
        EEPROM_PART_CNT_INVALID_BOOT_END,
        EEPROM_PART_CNT_INVALID_BOOT_SIZE
    },
    {
        EEPROM_PART_BOOT_CONFIG_NAME,
        EEPROM_PART_BOOT_CONFIG_MAGIC,
        EEPROM_PART_MAGIC_SIZE,
        0x0U,
        EEPROM_PART_BOOT_CONFIG_BEGIN,
        EEPROM_PART_BOOT_CONFIG_END,
        EEPROM_PART_BOOT_CONFIG_SIZE
    },
    {
        EEPROM_PART_BOOT_WIFI_CREDS_A_NAME,
        EEPROM_PART_BOOT_WIFI_CREDS_A_MAGIC,
        EEPROM_PART_MAGIC_SIZE,
        0x0U,
        EEPROM_PART_BOOT_WIFI_CREDS_A_BEGIN,
        EEPROM_PART_BOOT_WIFI_CREDS_A_END,
        EEPROM_PART_BOOT_WIFI_CREDS_A_SIZE
    },
    {
        EEPROM_PART_BOOT_WIFI_CREDS_B_NAME,
        EEPROM_PART_BOOT_WIFI_CREDS_B_MAGIC,
        EEPROM_PART_MAGIC_SIZE,
        0x0U,
        EEPROM_PART_BOOT_WIFI_CREDS_B_BEGIN,
        EEPROM_PART_BOOT_WIFI_CREDS_B_END,
        EEPROM_PART_BOOT_WIFI_CREDS_B_SIZE
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
    extmem_eeprom.partition_table = eeprom_part_table;
    extmem_eeprom.partition_table_size = sizeof(eeprom_part_table) / sizeof(partition_entry_t);

    return 0;
}
