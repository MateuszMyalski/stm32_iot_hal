#include "bsp.h"
#include "delay.h"
#include "eeprom.h"
#include "eeprom_map.h"
#include "modules.h"

static void init_device_info(void) {
    part_device_info_t device_info = {
        .magic = EEPROM_PART_DEVICE_INFO_MAGIC,
        .minor_bl_version = 0x01,    // TODO Take from header
        .major_bl_version = 0x00,    // TODO Take from header
        .minor_imgA_version = 0x00,  // TODO Take from header
        .major_imgA_version = 0x00,  // TODO Take from header
        .minor_imgB_version = 0x00,  // TODO Take from header
        .major_imgB_version = 0x00,  // TODO Take from header
        ._reserved = {0xEE},
        .crc32 = 0,
    };

    int err = 0;
    err = eeprom_store_partition(&extmem_eeprom, EEPROM_PART_DEVICE_INFO_NAME, (const uint8_t *)&device_info);
    delay_ms(BSP_EEPROM_WRITE_DELAY_MS);
    if (err) {
        error_blink();
    }
}

void factory_reset_eeprom(void) {
    init_device_info();
}

void get_device_info(part_device_info_t *device_info) {
    int err = 0;
    err = eeprom_load_partition(&extmem_eeprom, EEPROM_PART_DEVICE_INFO_NAME, (uint8_t *)device_info);
    if (err) {
        error_blink();
    }
}
