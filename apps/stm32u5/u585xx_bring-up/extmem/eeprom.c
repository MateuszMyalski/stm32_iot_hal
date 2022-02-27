#include "eeprom.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "crc32.h"
#include "logger.h"
#include "partition.h"

#define CRC_INIT_VALUE 0xFFFFFFFFUL

static bool is_magic_valid(const partition_entry_t *partition, const uint8_t *partion_buffer) {
    if ((partition->magic_size <= 0) || (partition->magic_size > MAX_PARTITON_NAME_SIZE)) {
        // Problem with partition magic size initialization
        return false;
    }

    return strncmp((const char *)partion_buffer, partition->magic, partition->magic_size) == 0;
}

eeprom_error_t eeprom_load_partition(const eeprom_t *eeprom, const char *part_name, uint8_t *buffer) {
    if ((NULL == part_name) || (NULL == buffer) || (NULL == eeprom)) {
        return EEPROM_ERROR;
    }

    if ((NULL == eeprom->partition_table) || (0 == eeprom->partition_table_size)) {
        return EEPROM_ERROR;
    }

    /* Look for partition */
    const partition_entry_t *partition = NULL;
    partition = extmem_partition_get_by_name(eeprom->partition_table, eeprom->partition_table_size, part_name);
    if (NULL == partition) {
        return EEPROM_ERROR_PARTITION_NOT_FOUND;
    }

    /* Read partition */
    eeprom_error_t err = EEPROM_ERROR_OK;
    err = eeprom->rx_data_cb(partition->begin_address, buffer, partition->length);
    if (err) {
        return EEPROM_ERROR_RX;
    }

    /* Validate magic */
    if (!(partition->flags & PARTITION_FLAG_NOT_VALIDATE_MAGIC) && !is_magic_valid(partition, buffer)) {
        return EEPROM_ERROR_MAGIC;
    }

    /* Check CRC */
    if (partition->flags & PARTITION_FLAG_USE_CRC) {
        return 0;
        uint16_t buffer_size_to_crc = partition->length - sizeof(uint64_t);
        uint64_t calc_crc = crc32(buffer, buffer_size_to_crc, CRC_INIT_VALUE);
        uint64_t part_crc = 0x0;
        memcpy(&part_crc, &buffer[buffer_size_to_crc], sizeof(uint64_t));

        if (calc_crc != part_crc) {
            return EEPROM_ERROR_CRC;
        }
    }

    return EEPROM_ERROR_OK;
}

eeprom_error_t eeprom_store_partition(const eeprom_t *eeprom, const char *part_name, const uint8_t *buffer) {
    if ((NULL == part_name) || (NULL == buffer) || (NULL == eeprom)) {
        return EEPROM_ERROR;
    }

    if ((NULL == eeprom->partition_table) || (0 == eeprom->partition_table_size)) {
        return EEPROM_ERROR;
    }

    /* Look for partition */
    const partition_entry_t *partition = NULL;
    partition = extmem_partition_get_by_name(eeprom->partition_table, eeprom->partition_table_size, part_name);
    if (NULL == partition) {
        return EEPROM_ERROR_PARTITION_NOT_FOUND;
    }

    /* Validate magic */
    if (!(partition->flags & PARTITION_FLAG_NOT_VALIDATE_MAGIC) && !is_magic_valid(partition, buffer)) {
        return EEPROM_ERROR_MAGIC;
    }

    /* Store partition data */
    eeprom_error_t err = EEPROM_ERROR_OK;
    err = eeprom->tx_data_cb(partition->begin_address, buffer, partition->length);
    if (err) {
        return EEPROM_ERROR_TX;
    }

    /* Compute CRC */
    if (partition->flags & PARTITION_FLAG_USE_CRC) {
        uint16_t buffer_no_crc_length = partition->length - sizeof(uint64_t);
        uint16_t part_crc_addr = partition->begin_address + buffer_no_crc_length;
        uint64_t calc_crc = crc32(buffer, buffer_no_crc_length, CRC_INIT_VALUE);

        // Send just CRC to not edit the source buffer
        err = eeprom->tx_data_cb(part_crc_addr, (const uint8_t *)&calc_crc, sizeof(uint64_t));
        if (err) {
            return EEPROM_ERROR_CRC;
        }
    }

    return EEPROM_ERROR_OK;
}

eeprom_error_t eeprom_erease_partition(const eeprom_t *eeprom, const char *part_name, uint8_t erease_symbol) {
    if ((NULL == part_name) || (NULL == eeprom)) {
        return EEPROM_ERROR;
    }

    if ((NULL == eeprom->partition_table) || (0 == eeprom->partition_table_size)) {
        return EEPROM_ERROR;
    }

    /* Look for partition */
    const partition_entry_t *partition = NULL;
    partition = extmem_partition_get_by_name(eeprom->partition_table, eeprom->partition_table_size, part_name);
    if (NULL == partition) {
        return EEPROM_ERROR_PARTITION_NOT_FOUND;
    }

    /* Clear the partition */
    uint8_t *empty_buffer = malloc(partition->length * sizeof(uint8_t));
    if (NULL == empty_buffer) {
        return EEPROM_ERROR;
    }

    memset(empty_buffer, erease_symbol, partition->length * sizeof(uint8_t));

    eeprom_error_t err = EEPROM_ERROR_OK;
    err = eeprom->tx_data_cb(partition->begin_address, empty_buffer, partition->length);
    if (err) {
        free(empty_buffer);
        return EEPROM_ERROR;
    }

    free(empty_buffer);

    return EEPROM_ERROR_OK;
}
