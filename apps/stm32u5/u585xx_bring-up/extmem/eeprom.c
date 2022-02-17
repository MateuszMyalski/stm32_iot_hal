#include "eeprom.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "partition.h"

#define CRC_INIT_VALUE 0xFFFFFFFFUL

static uint64_t crc32(const uint8_t *input, size_t input_size, uint64_t init);

static bool is_magic_valid(const partition_entry_t *partition, const uint8_t *partion_buffer) {
    if ((partition->magic_size <= 0) || (partition->magic_size > MAX_PARTITON_NAME_SIZE)) {
        // Problem with partition magic size initialization
        return false;
    }

    return strncmp((const char *)partion_buffer, partition->magic, partition->magic_size) == 0;
}

int eeprom_load_partition(const eeprom_t *eeprom, const char *part_name, uint8_t *buffer) {
    if ((NULL == part_name) || (NULL == buffer) || (NULL == eeprom)) {
        return -1;
    }

    if ((NULL == eeprom->partition_table) || (0 == eeprom->partition_table_size)) {
        // EEPROM is not using partitions
        return -1;
    }

    /* Look for partition */
    const partition_entry_t *partition = NULL;
    partition = extmem_partition_get_by_name(eeprom->partition_table, eeprom->partition_table_size, part_name);
    if (NULL == partition) {
        // Partition not found
        return -1;
    }

    /* Read partition */
    int err = 0;
    err = eeprom->rx_data_cb(partition->begin_address, buffer, partition->length);
    if (err) {
        // Error while reading partiton
        return -1;
    }

    /* Validate magic */
    if (!(partition->flags & PARTITION_FLAG_NOT_VALIDATE_MAGIC) && !is_magic_valid(partition, buffer)) {
        // Error in magic value
        return -1;
    }

    /* When necessary compute CRC */
    if (!(partition->flags & PARTITION_FLAG_USE_CRC)) {
        return 0;
    }

    /* Check CRC */
    size_t buffer_size_to_crc = partition->length - sizeof(uint64_t);
    uint64_t calc_crc = crc32(buffer, buffer_size_to_crc, CRC_INIT_VALUE);
    uint64_t part_crc = *(buffer + buffer_size_to_crc);
    if(calc_crc != part_crc) {
        // Error in crc
        return -1;
    }

    return 0;
}

int eeprom_store_partition(const eeprom_t *eeprom, const char *part_name, const uint8_t *buffer) {
    if ((NULL == part_name) || (NULL == buffer) || (NULL == eeprom)) {
        return -1;
    }

    if ((NULL == eeprom->partition_table) || (0 == eeprom->partition_table_size)) {
        // EEPROM is not using partitions
        return -1;
    }

    /* Look for partition */
    const partition_entry_t *partition = NULL;
    partition = extmem_partition_get_by_name(eeprom->partition_table, eeprom->partition_table_size, part_name);
    if (NULL == partition) {
        // Partition not found
        return -1;
    }

    /* Validate magic */
    if (!(partition->flags & PARTITION_FLAG_NOT_VALIDATE_MAGIC) && !is_magic_valid(partition, buffer)) {
        // Error in magic value
        return -1;
    }

    /* When necessary compute CRC */
    if (partition->flags & PARTITION_FLAG_USE_CRC) {
        size_t buffer_size_to_crc = partition->length - sizeof(uint64_t);
        uint64_t *crc_slot = buffer + buffer_size_to_crc;
        *crc_slot = crc32(buffer, buffer_size_to_crc, CRC_INIT_VALUE);
    }

    /* Store partition */
    int err = 0;
    err = eeprom->tx_data_cb(partition->begin_address, buffer, partition->length);
    if (err) {
        // Error while writting partiton
        return -1;
    }

    return 0;
}

int eeprom_erease_partition(const eeprom_t *eeprom, const char *part_name, uint8_t erease_symbol) {
    if ((NULL == part_name) || (NULL == eeprom)) {
        return -1;
    }

    if ((NULL == eeprom->partition_table) || (0 == eeprom->partition_table_size)) {
        // EEPROM is not using partitions
        return -1;
    }

    /* Look for partition */
    const partition_entry_t *partition = NULL;
    partition = extmem_partition_get_by_name(eeprom->partition_table, eeprom->partition_table_size, part_name);
    if (NULL == partition) {
        // Partition not found
        return -1;
    }

    /* Clear the partition */
    uint8_t *empty_buffer = malloc(partition->length * sizeof(uint8_t));
    if (NULL == empty_buffer) {
        // Error while allocating memory
        return -1;
    }

    memset(empty_buffer, erease_symbol, partition->length * sizeof(uint8_t));

    int err = 0;
    err = eeprom->tx_data_cb(partition->begin_address, empty_buffer, partition->length);
    if (err) {
        // Error while writting partiton
        return -1;
    }

    free(empty_buffer);

    return 0;
}
