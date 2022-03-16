#ifndef BSP_EEPROM_MAP_H
#define BSP_EEPROM_MAP_H

#include <assert.h>
#include <stdint.h>

#define EEPROM_PART_MAGIC_SIZE 8UL

#define EEPROM_SIZE      32000UL  // 256Kbit - 32Kbyte - 32000 bytes
#define EEPROM_PAGE_SIZE 64UL
#define EEPROM_BEGIN     0x0000UL

/* Note: The partition structure is as follows
 * -- magic
 * ----------
 * --
 * -- DATA
 * --
 * ----------
 * -- crc32
 */

typedef struct __attribute__((packed, aligned(1))) {
    uint8_t magic[EEPROM_PART_MAGIC_SIZE];
    uint16_t minor_bl_version;
    uint16_t major_bl_version;
    uint16_t minor_imgA_version;
    uint16_t major_imgA_version;
    uint16_t minor_imgB_version;
    uint16_t major_imgB_version;
    uint8_t _reserved[36];
    uint64_t crc32;
} part_device_info_t;

typedef struct __attribute__((packed, aligned(1))) {
    uint8_t magic[EEPROM_PART_MAGIC_SIZE];
    uint32_t invalid_boot_A;
    uint32_t invalid_boot_B;
    uint8_t _reserved[40];
    uint64_t crc32;
} part_cnt_invalid_boot_t;

typedef struct __attribute__((packed, aligned(1))) {
    uint8_t magic[EEPROM_PART_MAGIC_SIZE];
    uint32_t boot_flag_bl;
    uint32_t boot_flag_imgA;
    uint32_t boot_flag_imgB;
    uint32_t error_flag_bl;
    uint32_t error_flag_imgA;
    uint32_t error_flag_imgB;
    uint8_t _reserved[24];
    uint64_t crc32;
} part_boot_config_t;

typedef struct __attribute__((packed, aligned(1))) {
    uint8_t magic[EEPROM_PART_MAGIC_SIZE];
    uint8_t SSID[32];
    uint8_t password[32];
    uint8_t _reserved[48];
    uint64_t crc32;
} part_wifi_creds_A_t;

typedef struct __attribute__((packed, aligned(1))) {
    uint8_t magic[EEPROM_PART_MAGIC_SIZE];
    uint8_t SSID[32];
    uint8_t password[32];
    uint8_t _reserved[48];
    uint64_t crc32;
} part_wifi_creds_B_t;

#define EEPROM_PART_DEVICE_INFO_MAGIC \
    { 0x5e, 0x64, 0x65, 0x76, 0x69, 0x6e, 0x66, 0x6f }  // "^devinfo"
#define EEPROM_PART_DEVICE_INFO_NAME  "device_info"
#define EEPROM_PART_DEVICE_INFO_BEGIN EEPROM_BEGIN
#define EEPROM_PART_DEVICE_INFO_SIZE  EEPROM_PAGE_SIZE
#define EEPROM_PART_DEVICE_INFO_END   (EEPROM_PART_DEVICE_INFO_BEGIN + EEPROM_PART_DEVICE_INFO_SIZE)

#define EEPROM_PART_CNT_INVALID_BOOT_MAGIC \
    { 0x5e, 0x63, 0x6e, 0x74, 0x69, 0x6e, 0x76, 0x62 }  // "^cntinvb"
#define EEPROM_PART_CNT_INVALID_BOOT_NAME  "cnt_invalid_boot"
#define EEPROM_PART_CNT_INVALID_BOOT_BEGIN EEPROM_PART_DEVICE_INFO_END
#define EEPROM_PART_CNT_INVALID_BOOT_SIZE  EEPROM_PAGE_SIZE
#define EEPROM_PART_CNT_INVALID_BOOT_END   (EEPROM_PART_DEVICE_INFO_END + EEPROM_PART_CNT_INVALID_BOOT_SIZE)

#define EEPROM_PART_BOOT_CONFIG_MAGIC \
    { 0x5e, 0x62, 0x6f, 0x6f, 0x74, 0x63, 0x66, 0x67 }  // "^bootcfg"
#define EEPROM_PART_BOOT_CONFIG_NAME  "boot_config"
#define EEPROM_PART_BOOT_CONFIG_BEGIN EEPROM_PART_CNT_INVALID_BOOT_END
#define EEPROM_PART_BOOT_CONFIG_SIZE  EEPROM_PAGE_SIZE
#define EEPROM_PART_BOOT_CONFIG_END   (EEPROM_PART_BOOT_CONFIG_BEGIN + EEPROM_PART_BOOT_CONFIG_SIZE)

#define EEPROM_PART_BOOT_WIFI_CREDS_A_MAGIC \
    { 0x5e, 0x62, 0x63, 0x72, 0x65, 0x64, 0x77, 0x61 }  // "^bcredwa"
#define EEPROM_PART_BOOT_WIFI_CREDS_A_NAME  "boot_wifi_creds_A"
#define EEPROM_PART_BOOT_WIFI_CREDS_A_BEGIN EEPROM_PART_BOOT_CONFIG_END
#define EEPROM_PART_BOOT_WIFI_CREDS_A_SIZE  (2 * EEPROM_PAGE_SIZE)
#define EEPROM_PART_BOOT_WIFI_CREDS_A_END   (EEPROM_PART_BOOT_WIFI_CREDS_A_BEGIN + EEPROM_PART_BOOT_WIFI_CREDS_A_SIZE)

#define EEPROM_PART_BOOT_WIFI_CREDS_B_MAGIC \
    { 0x5e, 0x62, 0x63, 0x72, 0x65, 0x64, 0x77, 0x62 }  // "^bcredwb"
#define EEPROM_PART_BOOT_WIFI_CREDS_B_NAME  "boot_wifi_creds_B"
#define EEPROM_PART_BOOT_WIFI_CREDS_B_BEGIN EEPROM_PART_BOOT_WIFI_CREDS_A_END
#define EEPROM_PART_BOOT_WIFI_CREDS_B_SIZE  (2 * EEPROM_PAGE_SIZE)
#define EEPROM_PART_BOOT_WIFI_CREDS_B_END   (EEPROM_PART_BOOT_WIFI_CREDS_B_BEGIN + EEPROM_PART_BOOT_WIFI_CREDS_B_SIZE)

#if (EEPROM_PART_BOOT_WIFI_CREDS_B_END > EEPROM_SIZE)
#error "EEPROM memory overflown"
#endif

static_assert(EEPROM_PART_DEVICE_INFO_SIZE == sizeof(part_device_info_t), "Invalid partition size");
static_assert(EEPROM_PART_CNT_INVALID_BOOT_SIZE == sizeof(part_cnt_invalid_boot_t), "Invalid partition size");
static_assert(EEPROM_PART_BOOT_CONFIG_SIZE == sizeof(part_boot_config_t), "Invalid partition size");
static_assert(EEPROM_PART_BOOT_WIFI_CREDS_A_SIZE == sizeof(part_wifi_creds_A_t), "Invalid partition size");
static_assert(EEPROM_PART_BOOT_WIFI_CREDS_B_SIZE == sizeof(part_wifi_creds_B_t), "Invalid partition size");

#endif
