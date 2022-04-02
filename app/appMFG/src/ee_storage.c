#include "ee_storage.h"

#include "bsp.h"
#include "crc32.h"
#include "delay.h"
#include "hal_crc.h"
#include "hal_i2c.h"
#include "led_notifier.h"
#include "partmng.h"

extern volatile uint32_t SysTick_msTicks;

mempart_memory_t mempart_memory = {};
eeprom_ctx_t eeprom_ctx         = {};

partition_entry_t eeprom_part_table[] = {
    {EEPROM_PART_DEVICE_INFO_NAME, EEPROM_PART_DEVICE_INFO_MAGIC, EEPROM_PART_MAGIC_SIZE, PARTITION_FLAG_USE_CRC,
     EEPROM_PART_DEVICE_INFO_BEGIN, EEPROM_PART_DEVICE_INFO_END, EEPROM_PART_DEVICE_INFO_SIZE},
    {EEPROM_PART_CNT_INVALID_BOOT_NAME, EEPROM_PART_CNT_INVALID_BOOT_MAGIC, EEPROM_PART_MAGIC_SIZE, 0x0U,
     EEPROM_PART_CNT_INVALID_BOOT_BEGIN, EEPROM_PART_CNT_INVALID_BOOT_END, EEPROM_PART_CNT_INVALID_BOOT_SIZE},
    {EEPROM_PART_BOOT_CONFIG_NAME, EEPROM_PART_BOOT_CONFIG_MAGIC, EEPROM_PART_MAGIC_SIZE, 0x0U,
     EEPROM_PART_BOOT_CONFIG_BEGIN, EEPROM_PART_BOOT_CONFIG_END, EEPROM_PART_BOOT_CONFIG_SIZE},
    {EEPROM_PART_BOOT_WIFI_CREDS_A_NAME, EEPROM_PART_BOOT_WIFI_CREDS_A_MAGIC, EEPROM_PART_MAGIC_SIZE, 0x0U,
     EEPROM_PART_BOOT_WIFI_CREDS_A_BEGIN, EEPROM_PART_BOOT_WIFI_CREDS_A_END, EEPROM_PART_BOOT_WIFI_CREDS_A_SIZE},
    {EEPROM_PART_BOOT_WIFI_CREDS_B_NAME, EEPROM_PART_BOOT_WIFI_CREDS_B_MAGIC, EEPROM_PART_MAGIC_SIZE, 0x0U,
     EEPROM_PART_BOOT_WIFI_CREDS_B_BEGIN, EEPROM_PART_BOOT_WIFI_CREDS_B_END, EEPROM_PART_BOOT_WIFI_CREDS_B_SIZE}};

static void reset_device_info(void) {
    part_device_info_t device_info = {
        .magic              = EEPROM_PART_DEVICE_INFO_MAGIC,
        .minor_bl_version   = 0x01,  // TODO Take from header
        .major_bl_version   = 0x00,  // TODO Take from header
        .minor_imgA_version = 0x00,  // TODO Take from header
        .major_imgA_version = 0x00,  // TODO Take from header
        .minor_imgB_version = 0x00,  // TODO Take from header
        .major_imgB_version = 0x00,  // TODO Take from header
        ._reserved          = {0xEE},
        .crc32              = 0,
    };

    int err = 0;

    err = mempart_store(&mempart_memory, EEPROM_PART_DEVICE_INFO_NAME, (uint8_t *)&device_info);
    delay_ms(BSP_EEPROM_WRITE_DELAY_MS);
    if (err) {
        led_notifier_error_blink();
    }
}

void ee_storage_factory_reset(void) {
    reset_device_info();
}

void ee_storage_get_device_info(part_device_info_t *device_info) {
    int err = 0;

    err = mempart_load(&mempart_memory, EEPROM_PART_DEVICE_INFO_NAME, (uint8_t *)device_info);
    if (err) {
        led_notifier_error_blink();
    }
}

static int eeprom_tx_data(uint16_t mem_addr, const uint8_t *data, size_t size) {
    int err = 0;

    err = eeprom_write(&eeprom_ctx, mem_addr, data, size);

    return err;
}

static int eeprom_rx_data(uint16_t mem_addr, uint8_t *data, size_t size) {
    int err = 0;

    err = eeprom_read(&eeprom_ctx, mem_addr, data, size);

    return err;
}

static int eeprom_decrypt(const partition_entry_t *partiton_name, uint8_t *data) {
    return 0;
}

static int eeprom_encrypt(const partition_entry_t *partiton_name, uint8_t *data) {
    return 0;
}

static uint32_t eeprom_crc(const partition_entry_t *partition_name, const uint8_t *data, size_t size) {
    uint32_t crc        = 0x0;
    uint32_t polynomial = 0x04C11DB7;
    uint32_t init_crc   = 0xFFFFFFFF;

#ifdef USE_HW_ACCELERATED_CRC
    hal_err_t err = hal_crc_open(CRC);
    if (HAL_NO_ERR != err) {
        return init_crc;
    }

    err |= hal_crc_ioctl(CRC, CRC_IOCTL_IN_BYTE_REVERSED, NULL);
    err |= hal_crc_ioctl(CRC, CRC_IOCTL_OUT_REVERSED, NULL);
    err |= hal_crc_ioctl(CRC, CRC_IOCTL_SET_POLY, (void *)&polynomial);
    err |= hal_crc_ioctl(CRC, CRC_IOCTL_INIT_CRC, (void *)&init_crc);
    if (HAL_NO_ERR != err) {
        return init_crc;
    }

    err |= hal_crc_write(CRC, data, size);
    if (HAL_NO_ERR != err) {
        return init_crc;
    }

    hal_crc_read(CRC, &crc);
    hal_crc_close(CRC);
#else
    crc32_ctx_t crc_ctx = {
        .polynomial = polynomial, .init_crc = init_crc, .in_reversed = CRC32_IN_BYTE_REVERSE, .out_reversed = true};
    crc = crc32(&crc_ctx, data, size);
#endif  // USE_HW_ACCELERATED_CRC

    return ~crc;
}

int init_ee_storage(void) {
    eeprom_err_t err = EEPROM_NO_ERR;

    err = eeprom_init(&eeprom_ctx, BSP_EEPROM_ADDR, BSP_EEPROM_I2C, (uint32_t *)&SysTick_msTicks);
    if (EEPROM_NO_ERR != err) {
        led_notifier_error_blink();
    }

    err = eeprom_set_timeout(&eeprom_ctx, 100);
    if (EEPROM_NO_ERR != err) {
        led_notifier_error_blink();
    }

    mempart_memory.device               = M24256_D;
    mempart_memory.tx_data_cb           = eeprom_tx_data;
    mempart_memory.rx_data_cb           = eeprom_rx_data;
    mempart_memory.decrypt_cb           = eeprom_decrypt;
    mempart_memory.encrypt_cb           = eeprom_encrypt;
    mempart_memory.crc_cb               = eeprom_crc;
    mempart_memory.partition_table      = eeprom_part_table;
    mempart_memory.partition_table_size = sizeof(eeprom_part_table) / sizeof(*eeprom_part_table);

    return 0;
}