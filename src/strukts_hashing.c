#include "strukts_hashing.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/* rotates value to left by amount times (also known as circular shift) */
static uint32_t strukts_rotate_left(uint32_t value, uint8_t amount) {
    /* undef behavior for 0 or 32 */
    if ((amount < 1) | (amount > 31)) exit(EXIT_FAILURE);

    return value << amount | value >> (32 - amount);
}

static uint32_t strukts_build_remaining_chunk(const uint8_t* key, uint8_t remaining_bytes) {
    uint32_t final_chunk = 0;

    switch (remaining_bytes) {
        case 3:
            memcpy(&final_chunk, key, 3 * sizeof(uint8_t));  // final 3 bytes
            break;

        case 2:
            memcpy(&final_chunk, key, 2 * sizeof(uint8_t));  // final 2 bytes
            break;

        default:
            memcpy(&final_chunk, key, sizeof(uint8_t));  // final byte
            break;
    }

    return final_chunk;
}

uint32_t strukts_murmur3_hash(const uint8_t* key, size_t key_len, uint32_t seed) {
    /* constants of the algorithm */
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    const uint8_t r1 = 15;
    const uint8_t r2 = 13;
    const uint8_t m = 5;
    const uint32_t n = 0xe6546b64;

    /* algorithm local variables */
    uint32_t key_chunk = 0; /* buffer of 4 bytes */
    uint32_t hash = seed;

    /* 4 bytes chunk processing */
    for (size_t i = 0; i < key_len / 4; ++i) {
        /* copies 4 bytes into key chunk */
        memcpy(&key_chunk, key, sizeof(uint32_t));

        /* changes key pointer base address by 4 bytes (+4 indexes positions) */
        key += sizeof(uint32_t);

        /* MUR */
        key_chunk *= c1;
        key_chunk = strukts_rotate_left(key_chunk, r1); /* ROL */
        key_chunk *= c2;

        hash ^= key_chunk;
        hash = strukts_rotate_left(hash, r2);
        hash = (hash * m) + n;
    }

    /* remaining bytes (1, 2 or 3 chunks of 4-bytes words) */
    key_chunk = strukts_build_remaining_chunk(key, key_len & 3);

    /* MUR */
    key_chunk *= c1;
    key_chunk = strukts_rotate_left(key_chunk, r1); /* ROL */
    key_chunk *= c2;
    hash ^= key_chunk;

    /* final avalanche to guarantee that if a single bit is changed,
     * then at least 50% of the hash value is changed. */
    hash ^= key_len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;

    return hash;
}