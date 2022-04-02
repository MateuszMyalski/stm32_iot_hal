#ifndef MEMPART_H
#define MEMPART_H

#include "partmng.h"

typedef enum {
    MEMPART_NO_ERR                  = 0,
    MEMPART_ERR_PARAMS              = -1,
    MEMPART_ERR_PARTITION_NOT_FOUND = -2,
    MEMPART_ERR_RX                  = -3,
    MEMPART_ERR_TX                  = -4,
    MEMPART_ERR_CRC                 = -5,
    MEMPART_ERR_MAGIC               = -6,
    MEMPART_ERR_DECRYPTION          = -7,
    MEMPART_ERR_ENCRYPTION          = -8,
    MEMPART_ERR_EARASE              = -9
} mempart_err_t;

typedef enum { NO_DEVICE = 0x0, M24256_D } device_t;

typedef int (*tx_data_cb_t)(uint16_t mem_addr, const uint8_t *data, size_t size);
typedef int (*rx_data_cb_t)(uint16_t mem_addr, uint8_t *data, size_t size);
typedef int (*decrypt_cb_t)(const partition_entry_t *partiton_name, uint8_t *data);
typedef int (*encrypt_cb_t)(const partition_entry_t *partiton_name, uint8_t *data);
typedef uint32_t (*crc_cb_t)(const partition_entry_t *partition_name, const uint8_t *data, size_t size);

typedef struct {
    device_t device;
    tx_data_cb_t tx_data_cb;
    rx_data_cb_t rx_data_cb;
    decrypt_cb_t decrypt_cb;
    encrypt_cb_t encrypt_cb;
    crc_cb_t crc_cb;
    const partition_entry_t *partition_table;
    size_t partition_table_size;
} mempart_memory_t;

/**
 * @brief Load the partiton from memory into the buffer
 * @param memory - memory context
 * @param part_name - partition name
 * @param buffer - buffer where partition will be copied
 *                 The buffer size must be equal or greater than the partiton size
 * @return mempart error code. 0 - Success
 */
mempart_err_t mempart_load(const mempart_memory_t *memory, const char *part_name, uint8_t *buffer);

/**
 * @brief Store the partiton to memory memory from buffer
 * @param memory - memory context
 * @param part_name - partition name
 * @param buffer - buffer of the partition data that is going to be stored
 *                 The buffer size must be equal or greater than the partiton size.
 *                 Encryption is going to be perfomed on the buffer.
 *                 CRC calculation will be copied into the buffer.
 * @return mempart error code. 0 - Success
 */
mempart_err_t mempart_store(const mempart_memory_t *memory, const char *part_name, uint8_t *buffer);

/**
 * @brief Erease the partion section and overwrite the conent with erease_symbol
 * @param memory - memory context
 * @param part_name - partition name
 * @param erease_symbol - the symbol that overwrites the memory cells
 * @return mempart error code. 0 - Success
 */
mempart_err_t mempart_erease(const mempart_memory_t *memory, const char *part_name, uint8_t erease_symbol);

#endif
