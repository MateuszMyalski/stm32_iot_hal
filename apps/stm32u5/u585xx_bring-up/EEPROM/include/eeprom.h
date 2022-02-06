#ifndef EEPROM_H
#define EEPROM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum { NO_DEVICE = 0x0, M24256_D } device_t;

typedef int(*tx_data_cb_t(uint16_t mem_addr, const uint8_t *data, size_t len));
typedef int(*rx_data_cb_t(uint16_t mem_addr, uint8_t *data, size_t len));

#define MAX_PARTITON_NAME_LEN 32

typedef struct {
    char partition_name[MAX_PARTITON_NAME_LEN];
    uint16_t begin_address;
    uint16_t end_address;
    bool w_protect;
    bool r_protect;
} partition_entry_t;

typedef struct {
    device_t device;
    uint16_t page_size;
    size_t memory_size;
    size_t partition_table_len;
    tx_data_cb_t tx_data_cb;
    rx_data_cb_t rx_data_cb;
    partition_entry_t *partition_table;
} eeprom_t;

int eeprom_M4256_D_init(eeprom_t *eeprom, tx_data_cb_t tx_data_cb, rx_data_cb_t rx_data_cb,
                        partition_entry_t partition_table, size_t partition_table_len);

int eeprom_read_partition(eeprom_t *eeprom, char *partition_name, uint8_t *partition_buffer);
int eeprom_write_partition(eeprom_t *eeprom, char *partition_name, const uint8_t *partition_buffer);

int eeprom_read_partition_from(eeprom_t *eeprom, char *partition_name, uint8_t *partition_buffer, uint16_t begin_offset,
                               size_t len);
int eeprom_write_partition_from(eeprom_t *eeprom, char *partition_name, const uint8_t *partition_buffer, uint16_t begin_offset,
                               size_t len);

#endif
