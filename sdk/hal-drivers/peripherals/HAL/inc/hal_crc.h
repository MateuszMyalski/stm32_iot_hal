#ifndef HAL_CRC_H
#define HAL_CRC_H

#include "hal_common.h"

typedef enum {
    CRC_ioctl_poly_size_7bit,
    CRC_ioctl_poly_size_8bit,
    CRC_ioctl_poly_size_16bit,
    CRC_ioctl_poly_size_32bit,
    CRC_ioctl_out_reversed,
    CRC_ioctl_out_no_reversed,
    CRC_ioctl_in_no_reversed,
    CRC_ioctl_in_byte_reversed,
    CRC_ioctl_in_half_word_reversed,
    CRC_ioctl_in_word_reversed,
    CRC_ioctl_poly_crc16citt,
    CRC_ioctl_poly_crc16ibm,
    CRC_ioctl_poly_crc16t10dif,
    CRC_ioctl_poly_crc16dnp,
    CRC_ioctl_poly_crc16dect,
    CRC_ioctl_poly_crc32,
    CRC_ioctl_poly_crc32c,
    CRC_ioctl_poly_crc32k,
    CRC_ioctl_poly_crc32q
    
} CRC_ioctl_t;

/**
 * @brief Enables the AHB
 * @return HAL Error code. 0 - Success
 */
hal_err_t hal_crc_open();

/**
 * @brief Resets the AHB bus
 * @return HAL Error code. 0 - Success
 */
hal_err_t hal_crc_close();

/**
 * @brief Sets mode/type
 * @param gpio_ioctl - enumaration of function to set
 * @return HAL Error code. 0 - Success
 */
hal_err_t hal_crc_ioctl(CRC_ioctl_t CRC_ioctl);

/**
 * @brief Add data to update the crc
 * @param data_in - value to update the CRC
 * @return HAL Error code. 0 - Success
 */
hal_err_t hal_crc_write(uint32_t data_in);

/**
 * @brief Read value of calculated crc and resets the calculation
 * @param value_out - calculated crc
 * @return 0/1 - Digital value present on selected pin
 */
hal_err_t hal_crc_read(uint32_t *value_out);

hal_err_t hal_crc_poly_init(uint32_t data);

#endif
