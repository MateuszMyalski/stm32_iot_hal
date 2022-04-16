#ifndef APP_EE_STORAGE_H
#define APP_EE_STORAGE_H

#include "m24256.h"
#include "mempart.h"
#include "eeprom_map.h"

extern mempart_memory_t mempart_memory;
extern eeprom_ctx_t ee_memory;

/**
 * @brief Initialize EEPROM structure and partition table
 * @return 0 - on success, -1 - on error
 */
int init_ee_storage(void);

/**
 * @brief Reads device info from external storage.
 * @param device_info - device info partition structure
 * @return (void)
 */
void ee_storage_get_device_info(part_device_info_t *device_info);

/**
 * @brief Perform factory reset on all partitions in EEPROM memory
 * @return (void)
 */
void ee_storage_factory_reset(void);

#endif