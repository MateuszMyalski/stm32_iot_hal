#include "mempart.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "crc32.h"
#include "partmng.h"

static bool is_magic_valid(const partition_entry_t *partition, const uint8_t *partion_buffer) {
    if ((partition->magic_size <= 0) || (partition->magic_size > MAX_PARTITON_NAME_SIZE)) {
        // Problem with partition magic size initialization
        return false;
    }

    return strncmp((const char *)partion_buffer, partition->magic, partition->magic_size) == 0;
}

mempart_err_t mempart_load(const mempart_memory_t *mempart_memory, const char *part_name, uint8_t *buffer) {
    if ((NULL == part_name) || (NULL == buffer) || (NULL == mempart_memory)) {
        return MEMPART_ERR_PARAMS;
    }

    if ((NULL == mempart_memory->partition_table) || (0 == mempart_memory->partition_table_size)) {
        return MEMPART_ERR_PARTITION_NOT_FOUND;
    }

    /* Look for partition */
    const partition_entry_t *partition = NULL;
    partition = partition_get_by_name(mempart_memory->partition_table, mempart_memory->partition_table_size, part_name);
    if (NULL == partition) {
        return MEMPART_ERR_PARTITION_NOT_FOUND;
    }

    /* Read partition */
    mempart_err_t err = mempart_memory->rx_data_cb(partition->begin_address, buffer, partition->length);
    if (err) {
        return MEMPART_ERR_RX;
    }

    /* Decrypt the partiton */
    if (partition->flags & PARTITION_FLAG_ENCRYPTED) {
        if (NULL == mempart_memory->decrypt_cb) {
            return MEMPART_ERR_DECRYPTION;
        }

        err = mempart_memory->decrypt_cb(partition, buffer);
        if (err) {
            return MEMPART_ERR_DECRYPTION;
        }
    }

    /* Validate magic */
    if (!(partition->flags & PARTITION_FLAG_NOT_VALIDATE_MAGIC)) {
        if (!is_magic_valid(partition, buffer)) {
            return MEMPART_ERR_MAGIC;
        }
    }

    /* Check CRC */
    if (partition->flags & PARTITION_FLAG_USE_CRC) {
        uint16_t buffer_size_to_crc = partition->length - sizeof(uint32_t);
        uint32_t calc_crc           = mempart_memory->crc_cb(partition, buffer, buffer_size_to_crc);
        uint32_t part_crc           = 0x0;
        memcpy(&part_crc, &buffer[buffer_size_to_crc], sizeof(uint32_t));

        if (calc_crc != part_crc) {
            return MEMPART_ERR_CRC;
        }
    }

    return MEMPART_NO_ERR;
}

mempart_err_t mempart_store(const mempart_memory_t *mempart_memory, const char *part_name, uint8_t *buffer) {
    if ((NULL == part_name) || (NULL == buffer) || (NULL == mempart_memory)) {
        return MEMPART_ERR_PARAMS;
    }

    if ((NULL == mempart_memory->partition_table) || (0 == mempart_memory->partition_table_size)) {
        return MEMPART_ERR_PARTITION_NOT_FOUND;
    }

    /* Look for partition */
    const partition_entry_t *partition = NULL;
    partition = partition_get_by_name(mempart_memory->partition_table, mempart_memory->partition_table_size, part_name);
    if (NULL == partition) {
        return MEMPART_ERR_PARTITION_NOT_FOUND;
    }

    /* Validate magic */
    if (!(partition->flags & PARTITION_FLAG_NOT_VALIDATE_MAGIC)) {
        if (!is_magic_valid(partition, buffer)) {
            return MEMPART_ERR_MAGIC;
        }
    }

    int err = 0;

    /* Compute CRC */
    if (partition->flags & PARTITION_FLAG_USE_CRC) {
        uint32_t buffer_no_crc_length = partition->length - sizeof(uint32_t);
        uint32_t calc_crc             = mempart_memory->crc_cb(partition, buffer, buffer_no_crc_length);
        memcpy(&buffer[buffer_no_crc_length], &calc_crc, sizeof(uint32_t));

        if (err) {
            return MEMPART_ERR_CRC;
        }
    }

    /* Encrypt the partiton */
    if (partition->flags & PARTITION_FLAG_ENCRYPTED) {
        if (NULL == mempart_memory->encrypt_cb) {
            return MEMPART_ERR_ENCRYPTION;
        }

        err = mempart_memory->encrypt_cb(partition, buffer);
        if (err) {
            return MEMPART_ERR_ENCRYPTION;
        }
    }

    /* Store partition data */
    err = mempart_memory->tx_data_cb(partition->begin_address, buffer, partition->length);
    if (err) {
        return MEMPART_ERR_TX;
    }

    return MEMPART_NO_ERR;
}

mempart_err_t mempart_erease(const mempart_memory_t *mempart_memory, const char *part_name, uint8_t erease_symbol) {
    if ((NULL == part_name) || (NULL == mempart_memory)) {
        return MEMPART_ERR_PARAMS;
    }

    if ((NULL == mempart_memory->partition_table) || (0 == mempart_memory->partition_table_size)) {
        return MEMPART_ERR_PARTITION_NOT_FOUND;
    }

    /* Look for partition */
    const partition_entry_t *partition = NULL;
    partition = partition_get_by_name(mempart_memory->partition_table, mempart_memory->partition_table_size, part_name);
    if (NULL == partition) {
        return MEMPART_ERR_PARTITION_NOT_FOUND;
    }

    /* Clear the partition */
    uint8_t *empty_buffer = malloc(partition->length * sizeof(uint8_t));
    if (NULL == empty_buffer) {
        return MEMPART_ERR_EARASE;
    }

    memset(empty_buffer, erease_symbol, partition->length * sizeof(uint8_t));

    mempart_err_t err = mempart_memory->tx_data_cb(partition->begin_address, empty_buffer, partition->length);
    if (err) {
        free(empty_buffer);
        return MEMPART_ERR_TX;
    }

    free(empty_buffer);

    return MEMPART_NO_ERR;
}
