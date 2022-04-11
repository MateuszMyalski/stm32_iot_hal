#ifndef HAL_CRC_H
#define HAL_CRC_H

#include "hal_common.h"

typedef enum {
    /* [NULL] Sets the polynomial size to 8 bits. */
    CRC_IOCTL_POLY_SIZE_7BIT,

    /* [NULL] Sets the polynomial size to 8 bits. */
    CRC_IOCTL_POLY_SIZE_8BIT,

    /* [NULL] Sets the polynomial size to 16 bits. */
    CRC_IOCTL_POLY_SIZE_16BIT,

    /* [NULL] Sets the polynomial size to 32 bits. */
    CRC_IOCTL_POLY_SIZE_32BIT,

    /* [NULL] Reverse output on bit level. */
    CRC_IOCTL_OUT_REVERSED,

    /* [NULL]  Do not reverse the output. */
    CRC_IOCTL_OUT_NO_REVERSED,

    /* [NULL] Do not reverse the input. */
    CRC_IOCTL_IN_NO_REVERSED,

    /* [NULL] Reverse the input by byte. */
    CRC_IOCTL_IN_BYTE_REVERSED,

    /* [NULL] Reverse the input by hald word. */
    CRC_IOCTL_IN_HALF_WORD_REVERSED,

    /* [NULL] Reverse the input by word. */
    CRC_IOCTL_IN_WORD_REVERSED,

    /* [uint32_t] Set polynomial, default: 0x04C11DB7. */
    CRC_IOCTL_SET_POLY,

    /* [uint32_t] Set initliazliation vector default 0xFFFFFFFF. */
    CRC_IOCTL_INIT_CRC
} CRC_ioctl_t;

/**
 * @brief Prepare for starting operation on the CRC peripherial
 * @param ctx [in] CMSIS CRC handler
 * @return HAL Error code
 */
hal_err_t hal_crc_open(CRC_TypeDef* ctx);

/**
 * @brief Disable the CRC peripheral
 * @param ctx [in] CMSIS CRC handler
 * @return HAL Error code
 */
hal_err_t hal_crc_close(CRC_TypeDef* ctx);

/**
 * @brief Sets mode/type
 * @param ctx  [in]      CMSIS CRC handler
 * @param cmd  [in]      ioctl cmd enumeration
 * @param args [in/out]  arg defined command
 * @return HAL Error code
 */
hal_err_t hal_crc_ioctl(CRC_TypeDef* ctx, CRC_ioctl_t cmd, void* args);

/**
 * @brief Adds data and update the CRC state
 * @param ctx     [in] CMSIS CRC handler
 * @param data_in [in] value to update the CRC
 * @param size    [in] size of the input data
 * @return HAL Error code
 */
hal_err_t hal_crc_write(CRC_TypeDef* ctx, const uint8_t* data_in, size_t size);

/**
 * @brief Read value of calculated crc and reset the CRC state
 * @param ctx       [in]  CMSIS CRC handler
 * @param value_out [out] calculated crc
 * @return HAL Error code
 */
hal_err_t hal_crc_read(CRC_TypeDef* ctx, uint32_t* value_out);

#endif
