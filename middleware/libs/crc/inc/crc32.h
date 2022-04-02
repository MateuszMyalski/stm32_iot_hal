#ifndef CRC32_H
#define CRC32_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum { CRC32_IN_NO_REVERSE, CRC32_IN_BYTE_REVERSE } crc32_in_reversed_t;

typedef struct {
    uint32_t polynomial;  //!< Currently supported only 32bit polynomial
    uint32_t init_polynomial;
    crc32_in_reversed_t in_reversed;
    bool out_reversed;
} crc32_ctx_t;

/**
 * @brief Calculate CRC32 based on input
 * @note Not even 32bits-words are preapended with 0x0 bytes
 * @param ctx[in] - CRC32 Context structure
 * @param data[in] - Data from whuch CRC32 is computed on
 * @param size[in] - Lenght of the input buffer
 * @return Calculated CRC32
 */
uint32_t crc32(const crc32_ctx_t *ctx, const uint8_t *data, size_t size);

#endif
