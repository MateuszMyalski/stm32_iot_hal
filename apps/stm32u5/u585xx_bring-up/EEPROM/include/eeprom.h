#ifndef EEPROM_H
#define EEPROM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "mem_part.h"

typedef enum { NO_DEVICE = 0x0, M24256_D } device_t;

typedef int(*tx_data_cb_t(uint16_t mem_addr, const uint8_t *data, size_t len));
typedef int(*rx_data_cb_t(uint16_t mem_addr, uint8_t *data, size_t len));


#define MAX_PARTITON_NAME_LEN 32

typedef struct {
    device_t device;
    uint16_t page_size;
    size_t memory_size;
    tx_data_cb_t *tx_data_cb;
    rx_data_cb_t *rx_data_cb;
} eeprom_t;

int eeprom_M4256_D_init(eeprom_t *eeprom, tx_data_cb_t tx_data_cb, rx_data_cb_t rx_data_cb);
int eeprom_read_partition(const eeprom_t *eeprom, uint8_t *buffer, const partition_entry_t *part);
int eeprom_write_partition(const eeprom_t *eeprom, const uint8_t *buffer, const partition_entry_t *part);
int eeprom_write_and_check_partition(const eeprom_t *eeprom, const uint8_t *buffer, const partition_entry_t *part);
int eeprom_erease_partition(const eeprom_t *eeprom, const uint8_t *buffer, const partition_entry_t *part);

int eeprom_read_partition_from(const eeprom_t *eeprom, uint8_t *buffer, const partition_entry_t *part,
                               uint16_t begin_offset, size_t len);
int eeprom_write_partition_from(const eeprom_t *eeprom, const uint8_t *buffer, const partition_entry_t *part,
                                uint16_t begin_offset, size_t len);
int eeprom_write_and_check_partition_from(const eeprom_t *eeprom, const uint8_t *buffer, const partition_entry_t *part,
                                          uint16_t begin_offset, size_t len);

#endif
