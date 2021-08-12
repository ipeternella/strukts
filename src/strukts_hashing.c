#include "strukts_hashing.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strukts_types.h>

/********************** STATIC INLINE FUNCTIONS **********************/
static inline WORD rotate_left(WORD value, BYTE amount) {
    return value << amount | value >> (32 - amount);
}

static inline WORD mur(WORD hash, WORD block, bool final_rotate) {
    const WORD c1 = 0xcc9e2d51;
    const WORD c2 = 0x1b873593;
    const BYTE r1 = 15;
    const BYTE r2 = 13;
    const BYTE m = 5;
    const WORD n = 0xe6546b64;

    block *= c1;
    block = rotate_left(block, r1);
    block *= c2;
    hash ^= block;

    if (!final_rotate) return hash;

    hash = rotate_left(hash, r2);
    hash = (hash * m) + n;

    return hash;
}

static inline final_avalanche(WORD hash, size_t key_len) {
    /*
     * Final avalanche to guarantee that if a single bit of the key is changed,
     * then at least 50% of the final hash value is also changed.
     */
    hash ^= key_len;
    hash ^= (hash >> 16);
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;

    return hash;
}

static inline WORD build_final_block(const BYTE* key, BYTE remaining_bytes) {
    WORD final_block = 0;

    /*
     * Builds the final 32-bit block with possible remaining key bits. Notice that
     * if key_len is a multiple of 4, then the final block is composed only of 0 bits.
     */
    if (remaining_bytes == 3) memcpy(&final_block, key, 3 * sizeof(BYTE));
    if (remaining_bytes == 2) memcpy(&final_block, key, 2 * sizeof(BYTE));
    if (remaining_bytes == 1) memcpy(&final_block, key, 1 * sizeof(BYTE));

    return final_block;
}

/********************** PUBLIC FUNCTIONS **********************/
WORD strukts_murmur3_hash(const BYTE* key, size_t key_len, WORD seed) {
    WORD hash = seed;
    WORD block = 0;

    /* iterative block hashing of the whole key in 4-bytes blocks */
    for (size_t i = 0; i < key_len / 4; ++i) {
        memcpy(&block, key, sizeof(WORD));
        hash = mur(hash, block, true);

        key += sizeof(WORD);
    }

    block = build_final_block(key, key_len & 3);
    hash = mur(hash, block, false);

    return final_avalanche(hash, key_len);
}