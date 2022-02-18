#include "modules.h"
#include "bsp.h"
#include "eeprom.h"
#include "eeprom_map.h"

static void init_device_info(void) {
    part_device_info_t device_info =  {
        .magic = EEPROM_PART_DEVICE_INFO_MAGIC,
        .minor_bl_version = 0x01, //TODO Take from header
        .major_bl_version = 0x00, //TODO Take from header
        .minor_imgA_version = 0x00, //TODO Take from header
        .major_imgA_version = 0x00, //TODO Take from header
        .minor_imgB_version = 0x00, //TODO Take from header
        .major_imgB_version = 0x00, //TODO Take from header
        ._reserved = {0xEE},
        .crc32 = 0,
    };

    int err = 0;
    err = eeprom_store_partition(&extmem_eeprom, EEPROM_PART_DEVICE_INFO_NAME, (const uint8_t*)&device_info);
    delay_ms(BSP_EEPROM_WRITE_DELAY_MS);
    err = eeprom_load_partition(&extmem_eeprom, EEPROM_PART_DEVICE_INFO_NAME, (uint8_t*)&device_info);
    while(err);
}

// static void init_invalid_boot(void) {
    
// typedef struct __attribute__((packed, aligned(1))) {
//     uint8_t magic[EEPROM_PART_MAGIC_SIZE];
//     uint32_t invalid_boot_A;
//     uint32_t invalid_boot_B;
//     uint8_t _reserved[40];
//     uint64_t crc32;
// } part_cnt_invalid_boot_t;

// }

// static void init_boot_config(void) {
    
// typedef struct __attribute__((packed, aligned(1))) {
//     uint8_t magic[EEPROM_PART_MAGIC_SIZE];
//     uint32_t boot_flag_bl;
//     uint32_t boot_flag_imgA;
//     uint32_t boot_flag_imgB;
//     uint32_t error_flag_bl;
//     uint32_t error_flag_imgA;
//     uint32_t error_flag_imgB;
//     uint8_t _reserved[24];
//     uint64_t crc32;
// } part_boot_config_t;


// }

// static init_wifi_creds_A(void) {
//     typedef struct __attribute__((packed, aligned(1))) {
//     uint8_t magic[EEPROM_PART_MAGIC_SIZE];
//     uint8_t SSID[32];
//     uint8_t password[32];
//     uint8_t _reserved[48];
//     uint64_t crc32;
// } part_wifi_creds_A_t;


// }

// static init_wifi_creds_B(void) {
// typedef struct __attribute__((packed, aligned(1))) {
//     uint8_t magic[EEPROM_PART_MAGIC_SIZE];
//     uint8_t SSID[32];
//     uint8_t password[32];
//     uint8_t _reserved[48];
//     uint64_t crc32;
// } part_wifi_creds_B_t;
// }

void factory_reset_eeprom(void) {
    init_device_info();
}

void get_device_info(part_device_info_t *device_info) {
    int err = 0;
    err = eeprom_load_partition(&extmem_eeprom, EEPROM_PART_DEVICE_INFO_NAME, (uint8_t*)&device_info);

}
