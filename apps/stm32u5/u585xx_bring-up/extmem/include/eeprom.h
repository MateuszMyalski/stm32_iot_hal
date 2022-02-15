#ifndef EXTMEM_EEPROM_H
#define EXTMEM_EEPROM_H

#include "partition.h"

typedef enum { NO_DEVICE = 0x0, M24256_D } device_t;

typedef int (*tx_data_cb_t)(uint16_t mem_addr, const uint8_t *data, size_t len);
typedef int (*rx_data_cb_t)(uint16_t mem_addr, uint8_t *data, size_t len);

typedef struct {
    device_t device;
    uint16_t page_size;
    uint16_t memory_size;
    tx_data_cb_t tx_data_cb;
    rx_data_cb_t rx_data_cb;
    const partition_entry_t *partition_table; // Must be set to NULL when not used
    size_t partition_table_size; // Must be set to 0 when not used
} eeprom_t;

/**
 * @brief Load the partiton from eeprom memory into the buffer
 * @param eeprom - eeprom context
 * @param part_name - partition name
 * @param buffer - buffer where partition will be copied
 *                 The buffer size must be equal or greater than the partiton size
 * @return 0 - on success, -1 - on error
 */
int eeprom_load_partition(const eeprom_t *eeprom, const char* part_name, uint8_t *buffer);

/**
 * @brief Store the partiton to eeprom memory from buffer
 * @param eeprom - eeprom context
 * @param part_name - partition name
 * @param buffer - buffer of the partition data that is going to be stored
 *                 The buffer size must be equal or greater than the partiton size
 * @return 0 - on success, -1 - on error
 */
int eeprom_store_partition(const eeprom_t *eeprom, const char* part_name, const uint8_t *buffer);

/**
 * @brief Erease the partion section and overwrite the conent with erease_symbol
 * @param eeprom - eeprom context
 * @param part_name - partition name
 * @param erease_symbol - the symbol that overwrites the memory cells
 * @return 0 - on success, -1 - on error
 */
int eeprom_erease_partition(const eeprom_t *eeprom, const char* part_name, uint8_t erease_symbol);

int eeprom_write_and_verify_partition(const eeprom_t *eeprom, const uint8_t *buffer);

int eeprom_read_partition_from(const eeprom_t *eeprom, uint8_t *buffer,
                               uint16_t begin_offset, size_t len);
int eeprom_write_partition_from(const eeprom_t *eeprom, const uint8_t *buffer,
                                uint16_t begin_offset, size_t len);
int eeprom_write_and_verify_partition_from(const eeprom_t *eeprom, const uint8_t *buffer,
                                           uint16_t begin_offset, size_t len);

#endif