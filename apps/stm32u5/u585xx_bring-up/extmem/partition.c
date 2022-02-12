#include "partition.h"
#include <string.h>

const partition_entry_t* extmem_partition_get_by_name(const partition_entry_t* part_table, size_t part_table_len,
                                                   const char* name) {
    if ((NULL == part_table) || (NULL == name) || (0 == part_table_len)) {
        return NULL;
    }

    for (size_t i = 0; i < part_table_len; i++) {
        if (strncmp(part_table[i].name, name, MAX_PARTITON_NAME_LEN) == 0) {
            return &part_table[i];
        }
    }

    return NULL;
}

const partition_entry_t* extmem_partition_get_by_addr(const partition_entry_t* part_table, size_t part_table_len,
                                                   uint16_t addr) {
    if ((NULL == part_table) || (0 == part_table_len)) {
        return NULL;
    }

    for (size_t i = 0; i < part_table_len; i++) {
        if ((addr >= part_table[i].begin_address) && (addr <= part_table[i].end_address)) {
            return &part_table[i];
        }
    }

    return NULL;
}
