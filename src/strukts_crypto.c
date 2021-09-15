#include "strukts_crypto.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/********************** SHA-256 ALGORITHMS'S SCHEDULE CONSTANTS **********************/
static const WORD SCHEDULE_CONSTANTS[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

/********************** MACROS **********************/
#define ROTATE_RIGHT(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define S0(x) (ROTATE_RIGHT(x, 7) ^ ROTATE_RIGHT(x, 18) ^ ((x) >> 3))
#define S1(x) (ROTATE_RIGHT(x, 17) ^ ROTATE_RIGHT(x, 19) ^ ((x) >> 10))
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define ROTATIONS_0(x) (ROTATE_RIGHT(x, 2) ^ ROTATE_RIGHT(x, 13) ^ ROTATE_RIGHT(x, 22))
#define ROTATIONS_1(x) (ROTATE_RIGHT(x, 6) ^ ROTATE_RIGHT(x, 11) ^ ROTATE_RIGHT(x, 25))

/********************** PRIVATE STRUCTS **********************/
typedef struct {
    WORD h0;
    WORD h1;
    WORD h2;
    WORD h3;
    WORD h4;
    WORD h5;
    WORD h6;
    WORD h7;
} StruktsCtxSHA256;

/********************** STATIC INLINE FUNCTIONS **********************/
static inline void sha256_fill_block(BYTE block[], short int block_position)
{
    for (short int i = block_position; i < 64; i++)
        block[i] = 0;
}

static inline void sha256_schedule_block(const BYTE block[], WORD schedule[])
{
    short int i;
    short int j;

    /* moves 4 bytes from block[] into 1 word of schedule[] */
    for (i = 0, j = 0; i < 16; i++, j += 4) {
        schedule[i] =
            (block[j] << 24) | (block[j + 1] << 16) | (block[j + 2] << 8) | (block[j + 3]);
    }
}

static inline void sha256_move_word(WORD word, BYTE hash[], short int start)
{
    short int j = 0;
    short int i = 0;

    for (i = start, j = 24; j >= 0; i++, j -= 8)
        hash[i] = word >> j;
}

/********************** STATIC FUNCTIONS **********************/
static void sha256_add_block_padding(BYTE block[], short int block_position, size_t msg_len,
                                     bool append_bit)
{
    uint64_t len = msg_len;
    short int shift = 56;

    /* appends 1 bit */
    if (append_bit) {
        block[block_position] = 1;
        block[block_position] <<= 7;
    }

    /* appends 64 bits containing msg_len at the end */
    for (short int i = 56; i < 64; i++) {
        block[i] = (BYTE)(len * 8 >> shift);
        shift -= 8;
    }
}

static void sha256_process_block(StruktsCtxSHA256* ctx, const BYTE block[])
{
    WORD a, b, c, d, e, f, g, h, tmp1, tmp2;
    WORD schedule[64] = {0};

    /* initial state according to previous iterations */
    a = ctx->h0;
    b = ctx->h1;
    c = ctx->h2;
    d = ctx->h3;
    e = ctx->h4;
    f = ctx->h5;
    g = ctx->h6;
    h = ctx->h7;

    /* moves block (512 bits = 16 x 32 bits words) into schedule[0 .. 15] words */
    sha256_schedule_block(block, schedule);

    /* extend block to the rest of the schedule array */
    for (short int i = 16; i < 64; i++)
        schedule[i] =
            schedule[i - 16] + S0(schedule[i - 15]) + schedule[i - 7] + S1(schedule[i - 2]);

    /* Davies-Meyer single-block-length of 512 bits compression */
    for (short int i = 0; i < 64; i++) {
        tmp1 = h + ROTATIONS_1(e) + CH(e, f, g) + SCHEDULE_CONSTANTS[i] + schedule[i];
        tmp2 = ROTATIONS_0(a) + MAJ(a, b, c);

        h = g;
        g = f;
        f = e;
        e = d + tmp1;
        d = c;
        c = b;
        b = a;
        a = tmp1 + tmp2;
    }

    /* update sha256 state for next block */
    ctx->h0 += a;
    ctx->h1 += b;
    ctx->h2 += c;
    ctx->h3 += d;
    ctx->h4 += e;
    ctx->h5 += f;
    ctx->h6 += g;
    ctx->h7 += h;
}

static BYTE* sha256_build_digest(const StruktsCtxSHA256* sha256_ctx)
{
    BYTE* hash = (BYTE*)calloc(32, sizeof(BYTE)); /* 256 bits digest */

    sha256_move_word(sha256_ctx->h0, hash, 0);
    sha256_move_word(sha256_ctx->h1, hash, 4);
    sha256_move_word(sha256_ctx->h2, hash, 8);
    sha256_move_word(sha256_ctx->h3, hash, 12);
    sha256_move_word(sha256_ctx->h4, hash, 16);
    sha256_move_word(sha256_ctx->h5, hash, 20);
    sha256_move_word(sha256_ctx->h6, hash, 24);
    sha256_move_word(sha256_ctx->h7, hash, 28);

    return hash;
}

/********************** PUBLIC FUNCTIONS **********************/
BYTE* strukts_crypto_sha256(const BYTE msg[], size_t msg_len)
{
    /* initial struct state with SHA-256's nothing-up-my-sleeve constants */
    StruktsCtxSHA256 sha256_ctx = {.h0 = 0x6a09e667,
                                   .h1 = 0xbb67ae85,
                                   .h2 = 0x3c6ef372,
                                   .h3 = 0xa54ff53a,
                                   .h4 = 0x510e527f,
                                   .h5 = 0x9b05688c,
                                   .h6 = 0x1f83d9ab,
                                   .h7 = 0x5be0cd19};

    short int block_position = 0; /* up to 64 (64 bytes = 512 bits) */
    BYTE block[64] = {0};         /* stores 512-bit blocks */

    /*
     * Merkle-Damgard's iterative hashing which processes all bytes of
     * the original msg in blocks of 512 bits using a sequence of
     * Davies-Meyer compresssion functions.
     */
    for (size_t i = 0; i < msg_len; i++) {
        /* starts building a 512-bit block */
        block[block_position++] = msg[i];

        /* 512 bits (64 bytes) complete block has been built */
        if (block_position == 64) {
            block_position = 0;
            sha256_process_block(&sha256_ctx, block);
        }
    }

    /* always fill with zeros the remaining bytes of the current block */
    sha256_fill_block(block, block_position);

    /*
     * Checks if the current block supports the extra 1 bit and the
     * 64-bit message length padding (extra 65 bits). As the SHA-256
     * requires blocks of 512 bits, if block_position * 8 + 65 > 512,
     * this means that the current block cannot hold the extra 65 bits,
     * so we should append the extra 1 bit to the current block, process
     * it and then create one extra final 512-bit block with the missing
     * message length padding that is required by SHA-256.
     */
    if (block_position * 8 + 65 > 512) {
        /* finish current block with 1 extra bit and process it */
        block[block_position] = 1;
        block[block_position] <<= 7;
        sha256_process_block(&sha256_ctx, block);

        /* creates the final extra block */
        sha256_fill_block(block, 0);
        sha256_add_block_padding(block, 0, msg_len, false);
        sha256_process_block(&sha256_ctx, block);

        /* use final ctx to build the final 256-bit hash value */
        return sha256_build_digest(&sha256_ctx);
    }

    /*
     * If we have reached here, it means that the current 512-bit block can
     * accomodate the 1 extra bit plus the 64-bit message length padding
     * (extra 65 bits). Hence, no extra 512-bit block is required and this
     * is the final block to process, so we add padding to this block and process it.
     */
    sha256_add_block_padding(block, block_position, msg_len, true);
    sha256_process_block(&sha256_ctx, block);

    return sha256_build_digest(&sha256_ctx);
}