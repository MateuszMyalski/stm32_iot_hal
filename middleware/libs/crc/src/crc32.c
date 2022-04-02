#include "crc32.h"

#include "limits.h"

#define CRC32_BIT (CHAR_BIT * sizeof(uint32_t))

static uint32_t revX_bits(uint32_t in, int n_bits) {
    uint32_t out = 0x0;

    int last_bit = (n_bits - 1);
    for (int i = 0; i < n_bits; i++) {
        out |= (in & 0b1) << (last_bit - i);
        in >>= 1;
    }

    return out;
}

static uint32_t byte_reverse(uint32_t in) {
    uint32_t out = 0x0;
    out |= revX_bits(in, CHAR_BIT);
    out |= revX_bits(in >> 8, CHAR_BIT) << 8;
    out |= revX_bits(in >> 16, CHAR_BIT) << 16;
    out |= revX_bits(in >> 24, CHAR_BIT) << 24;

    return out;
}

static uint32_t calculate_crc32(uint32_t init, uint32_t data, uint32_t polynomial, crc32_in_reversed_t in_reversed) {
    switch (in_reversed) {
        case CRC32_IN_BYTE_REVERSE:
            data = byte_reverse(data);
            break;

        case CRC32_IN_NO_REVERSE:
            /* fallthrough */

        default:
            break;
    }

    uint32_t crc = init ^ data;

    for (int i = 0; i < CRC32_BIT; i++) {
        if (crc & 0x80000000) {
            crc = (crc << 1) ^ polynomial;
        } else {
            crc = (crc << 1);
        }
    }

    return crc;
}

inline static uint32_t byte_swap32(const uint8_t *in) {
    return in[3] | (in[2] << 8) | (in[1] << 16) | (in[0] << 24);
}

inline static uint32_t align_to_word(const uint8_t *in, int size) {
    uint32_t out = 0x0;
    for (int i = 0; i < size; i++) {
        out |= in[i] << (8 * i);
    }
    return out;
}

uint32_t crc32(const crc32_ctx_t *ctx, const uint8_t *data_in, size_t size) {
    if ((NULL == ctx) || (NULL == data_in) || (0 > size)) {
        return 0xFFFFFFFF;
    }

    uint32_t crc = ctx->init_crc;

    /* Calculate how many even words contain the array (floor the division) */
    size_t n_words = size / sizeof(uint32_t);

    /* Calculate CRC of even 32bit-words */
    for (size_t i = 0; i < (n_words * sizeof(uint32_t)); i += sizeof(uint32_t)) {
        const uint8_t *aligned_word = data_in + i;
        uint32_t data               = byte_swap32(aligned_word);

        crc = calculate_crc32(crc, data, ctx->polynomial, ctx->in_reversed);
    }

    /* Calculate last not aligned bytes */
    size_t n_bytes = size - (n_words * sizeof(uint32_t));
    if (0 < n_bytes) {
        const uint8_t *not_aligned_word = data_in + n_words * sizeof(uint32_t);
        uint32_t data                   = align_to_word(not_aligned_word, n_bytes);

        crc = calculate_crc32(crc, data, ctx->polynomial, ctx->in_reversed);
    }

    return ctx->out_reversed ? revX_bits(crc, CRC32_BIT) : crc;
}
