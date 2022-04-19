#ifndef M24256_H
#define M24256_H

#include <stddef.h>
#include <stdint.h>

#include "hal_common.h"

typedef enum {
    EEPROM_NO_ERR      = 0,
    EEPROM_ERR_READ    = -1,
    EEPROM_ERR_WRITE   = -2,
    EEPROM_ERR_PARAMS  = -3,
    EEPROM_ERR_TIMEOUT = -4,
    EEPROM_ERR_NOT_IMPLEMENTED = -5
} eeprom_err_t;

typedef struct {
    uint8_t device_address;
    I2C_TypeDef *I2C;
    uint32_t page_size;
    uint32_t memory_size;
    const uint32_t *ms_tick_source;
    uint32_t timeout;
} eeprom_ctx_t;

/**
 * @brief Initialzie the EEPROM context
 * @param eeprom_ctx - EEPROM context struct
 * @param device_address - EPPROM I2C address
 * @param I2C - CMSIS I2C context
 * @param ms_tick_source - Milisecond tick source variable. (Can be null in case not using)
 * @return EEPROM Error code. 0 - Success
 */
eeprom_err_t eeprom_init(eeprom_ctx_t *eeprom_ctx, uint8_t device_address, I2C_TypeDef *I2C,
                         const uint32_t *ms_tick_source);

/**
 * @brief Set the timeout for active polling
 * @param eeprom_ctx - EEPROM context struct
 * @param timeout_ms - Timeout in ms. 0 - means no timeout (defualt)
 * @return EEPROM Error code. 0 - Success
 */
eeprom_err_t eeprom_set_timeout(eeprom_ctx_t *eeprom_ctx, uint32_t timeout_ms);

/**
 * @brief Write data to the eeprom memory
 * @param eeprom_ctx - EEPROM context struct
 * @param mem_addr - address of the cell to start the write
 * @param data - data to write
 * @param size - data to write length
 * @return EEPROM Error code. 0 - Success
 */
eeprom_err_t eeprom_write(eeprom_ctx_t *eeprom_ctx, uint16_t mem_addr, const uint8_t *data, size_t size);

/**
 * @brief Read data to the eeprom memory
 * @param eeprom_ctx - EEPROM context struct
 * @param mem_addr - address of the cell to start the read
 * @param data - data to read
 * @param size - data to read length
 * @return EEPROM Error code. 0 - Success
 */
eeprom_err_t eeprom_read(eeprom_ctx_t *eeprom_ctx, uint16_t mem_addr, uint8_t *data, size_t size);

#endif
