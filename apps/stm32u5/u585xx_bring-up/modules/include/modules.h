#ifndef MODULES_MODULES_H
#define MODULES_MODULES_H

#include <stdbool.h>
#include "eeprom_map.h"

/**
 * @brief Perform simple test on HTS221 sensor to test I2C connection.
 * @return (void)
 */
void hts221_simple_test(void);

/**
 * @brief Notify error by running LED seqence.
 * @return (void)
 */
void error_blink(void);

/**
 * @brief Perform all necessary stages to revert device to the factory state.
 * @return (void)
 */
void handle_factory_reset(void);

/**
 * @brief Check if factory reset should be perforemd.
 * @return 1 - factory reset should be performed,
 *         0 - no factory reset trigger found
 */
bool check_factory_reset_trigger(void);

/**
 * @brief Perform LED sequence to notify that the device is not in asssert.
 * @return (void)
 */
void idle_notifier(void);

/**
 * @brief Reads device info from external storage.
 * @param device_info - device info partition structure
 * @return (void)
 */
void get_device_info(part_device_info_t *device_info);

#endif
