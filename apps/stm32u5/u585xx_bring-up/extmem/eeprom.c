#include "eeprom.h"
#include "partition.h"

static bool is_magic_valid(const partition_entry_t *partition, const uint8_t *partion_buffer) {
    if ((partition->magic_size <= 0) || (partition->magic_size > MAX_PARTITON_NAME_SIZE)) {
        // Problem with partition magic size initialization
        return false;
    }

    return strncmp(partion_buffer, partition->magic, partition->magic_size);
}

int eeprom_load_partition(const eeprom_t *eeprom, const char *part_name, uint8_t *buffer) {
    if ((NULL == part_name) || (NULL == part_name) || (NULL == eeprom)) {
        return -1;
    }

    if ((NULL == eeprom->partition_table) || (0 == eeprom->partition_table_size)) {
        // EEPROM is not using partitions
        return -1;
    }

    /* Look for partition */
    const partition_entry_t *partition = NULL;
    partition = mem_partition_get_by_name(eeprom->partition_table, eeprom->partition_table_size, part_name);
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
    // TODO

    return 0;
}

int eeprom_store_partition(const eeprom_t *eeprom, const char *part_name, const uint8_t *buffer) {
    return 0;
}

int eeprom_erease_partition(const eeprom_t *eeprom, const char *part_name, uint8_t erease_symbol) {
    return 0;
}
