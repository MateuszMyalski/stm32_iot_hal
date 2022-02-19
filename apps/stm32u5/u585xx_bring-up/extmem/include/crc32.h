#ifndef EXTMEM_CRC32_H
#define EXTMEM_CRC32_H

#include <stdint.h>
#include <stddef.h>

/**
 * @brief Calculate CRC32 based on input
 * @param input - Data from which CRC32 is computed on
 * @param input_size - lenght of the input buffer
 * @param init - initialization vector
 * @return calculated CRC32
 */
uint64_t crc32(const uint8_t *input, size_t input_size, uint64_t init);

#endif
