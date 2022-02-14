#ifndef EXTMEM_PARTITION_H
#define EXTMEM_PARTITION_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define MAX_PARTITON_NAME_LEN 32

typedef enum {
    PARTITION_FLAG_WRITE_PROTECT = 1U,
    PARTITION_FLAG_READ_PROTECT = (1U << 2UL),
    PARTITION_FLAG_ENCRYPTED = (1U << 3UL),
} partition_flag_t;

typedef struct {
    char name[MAX_PARTITON_NAME_LEN];
    uint32_t flags;
    uint16_t begin_address;
    uint16_t end_address;
    uint16_t length;
} partition_entry_t;

/**
 * @brief Find partition in table by it's name
 * @param part_table Array of structs - partition table
 * @param part_table_len - Length of the partition table
 * @param name - Partition name
 * @return NULL - when not found / in case found partition pointer to the partition entry
 */
const partition_entry_t* mem_partition_get_by_name(const partition_entry_t* part_table, size_t part_table_len,
                                                   const char* name);

/**
 * @brief Find partition by the address
 * @param part_table Array of structs - partition table
 * @param part_table_len - Length of the partition table
 * @param addr - Memory address
 * @return NULL - when not found / in case found partiition pointer to the partition entry
 */
const partition_entry_t* mem_partition_get_by_addr(const partition_entry_t* part_table, size_t part_table_len,
                                                   uint16_t addr);

#endif
