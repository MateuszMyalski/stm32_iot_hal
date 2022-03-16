#include "partmng.h"

#include <string.h>

const partition_entry_t* partition_get_by_name(const partition_entry_t* part_table, size_t part_table_size,
                                               const char* name) {
    if ((NULL == part_table) || (NULL == name) || (0 == part_table_size)) {
        return NULL;
    }

    for (size_t i = 0; i < part_table_size; i++) {
        if (strncmp(part_table[i].name, name, MAX_PARTITON_NAME_SIZE) == 0) {
            return &part_table[i];
        }
    }

    return NULL;
}

const partition_entry_t* partition_get_by_addr(const partition_entry_t* part_table, size_t part_table_size,
                                               uint16_t addr) {
    if ((NULL == part_table) || (0 == part_table_size)) {
        return NULL;
    }

    for (size_t i = 0; i < part_table_size; i++) {
        if ((addr >= part_table[i].begin_address) && (addr <= part_table[i].end_address)) {
            return &part_table[i];
        }
    }

    return NULL;
}
