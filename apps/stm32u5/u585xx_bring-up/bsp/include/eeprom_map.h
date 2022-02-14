#ifndef BSP_AP_H
#define BSP_AP_H

#include <stdint.h>
#include <assert.h>

#define EEPROM_SIZE         32000UL // 256Kbit - 32Kbyte - 32000 bytes
#define EEPROM_PAGE_SIZE    64UL

typedef struct __attribute__((packed, aligned(1))) {
    uint8_t minor_bl_version;
    uint8_t major_bl_version;
    uint8_t minor_imgA_version;
    uint8_t major_imgA_version;
    uint8_t minor_imgB_version;
    uint8_t major_imgB_version;
    uint8_t _reserved[2];
} part_device_info_t;
static_assert(EEPROM_PAGE_SIZE != sizeof(part_device_info_t));

typedef struct __attribute__((packed, aligned(1))) {
    uint32_t invalid_boot_A;
} part_cnt_invalid_boot_A_t;
static_assert(32UL != sizeof(part_cnt_invalid_boot_A_t));

typedef struct __attribute__((packed, aligned(1))) {
    uint32_t invalid_boot_B;
} part_cnt_invalid_boot_B_t;
static_assert(32UL != sizeof(part_cnt_invalid_boot_B_t));

typedef struct __attribute__((packed, aligned(1))) {
    uint8_t boot_flag_bl;
    uint8_t boot_flag_imgA;
    uint8_t boot_flag_imgB;
    uint8_t error_flag_bl;
    uint8_t error_flag_imgA;
    uint8_t error_flag_imgB;
    uint8_t _reserved[16];
} part_boot_config_t;
static_assert(EEPROM_PAGE_SIZE != sizeof(part_boot_config_t));

typedef struct __attribute__((packed, aligned(1))) {
    uint8_t SSID[32];
    uint8_t password[32];
} part_wifi_creds_A_t;
static_assert(EEPROM_PAGE_SIZE != sizeof(part_wifi_creds_A_t));

typedef struct __attribute__((packed, aligned(1))) {
    uint8_t SSID[32];
    uint8_t password[32];
} part_wifi_creds_B_t;
static_assert(EEPROM_PAGE_SIZE != sizeof(part_wifi_creds_B_t));

#define DEVICE_INFO_NAME            "device_info"
#define DEVICE_INFO_BEGIN           0x0000U
#define DEVICE_INFO_LEN             64UL
#define DEVICE_INFO_END             (DEVICE_INFO_BEGIN + DEVICE_INFO_LEN)

#define CNT_INVALID_BOOT_A_NAME     "cnt_invalid_boot_A"
#define CNT_INVALID_BOOT_A_BEGIN    DEVICE_INFO_END
#define CNT_INVALID_BOOT_A_LEN      32UL
#define CNT_INVALID_BOOT_A_END      (DEVICE_INFO_END + CNT_INVALID_BOOT_A_LEN)

#define CNT_INVALID_BOOT_B_NAME     "cnt_invalid_boot_B"
#define CNT_INVALID_BOOT_B_BEGIN    CNT_INVALID_BOOT_A_END
#define CNT_INVALID_BOOT_B_LEN      32UL
#define CNT_INVALID_BOOT_B_END      (CNT_INVALID_BOOT_B_BEGIN + CNT_INVALID_BOOT_B_LEN)

#define BOOT_CONFIG_NAME            "boot_config"
#define BOOT_CONFIG_BEGIN           CNT_INVALID_BOOT_B_END
#define BOOT_CONFIG_LEN             64UL
#define BOOT_CONFIG_END             (BOOT_CONFIG_BEGIN + BOOT_CONFIG_LEN)

#define BOOT_WIFI_CREDS_A_NAME      "boot_wifi_creds_A"
#define BOOT_WIFI_CREDS_A_BEGIN     BOOT_CONFIG_END
#define BOOT_WIFI_CREDS_A_LEN       64UL
#define BOOT_WIFI_CREDS_A_END       (BOOT_WIFI_CREDS_A_BEGIN + BOOT_WIFI_CREDS_A_LEN)

#define BOOT_WIFI_CREDS_B_NAME      "boot_wifi_creds_A"
#define BOOT_WIFI_CREDS_B_BEGIN     BOOT_WIFI_CREDS_A_END
#define BOOT_WIFI_CREDS_B_LEN       64UL
#define BOOT_WIFI_CREDS_B_END       (BOOT_WIFI_CREDS_B_BEGIN + BOOT_WIFI_CREDS_B_LEN)

#if (BOOT_WIFI_CREDS_B_END > EEPROM_SIZE)
#error "EEPROM memory overflown"
#endif

#endif
