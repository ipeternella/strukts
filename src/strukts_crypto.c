#include "strukts_crypto.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/********************** SHA-256 ALGORITHMS'S CONSTANTS **********************/
static const WORD schedule_constants[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

static const WORD h0 = 0x6a09e667;
static const WORD h1 = 0xbb67ae85;
static const WORD h2 = 0x3c6ef372;
static const WORD h3 = 0xa54ff53a;
static const WORD h4 = 0x510e527f;
static const WORD h5 = 0x9b05688c;
static const WORD h6 = 0x1f83d9ab;
static const WORD h7 = 0x5be0cd19;

/********************** STATIC INLINE FUNCTIONS **********************/
static inline WORD rotate_right(WORD x, short int n) { return x >> n | x << (32 - n); }

static inline void move_word(WORD word, BYTE hash[], short int start) {
    short int j = 0;
    short int i = 0;

    for (i = start, j = 24; j >= 0; i++, j -= 8) hash[i] = word >> j;
}

static inline void sha256_prepare_chunk(BYTE chunk[], short int chunk_position) {
    for (short int i = chunk_position; i < 64; i++) chunk[i] = 0;
}

static inline StruktsCtxSHA256 strukts_ctx_sha256_new() {
    return (StruktsCtxSHA256){
        .h0 = h0, .h1 = h1, .h2 = h2, .h3 = h3, .h4 = h4, .h5 = h5, .h6 = h6, .h7 = h7};
}

/********************** STATIC FUNCTIONS **********************/
static void schedule_chunk(BYTE chunk[], WORD schedule[]) {
    short int i;
    short int j;

    /* moves 4 bytes from chunk[] into 1 word of schedule[] */
    for (i = 0, j = 0; i < 16; i++, j += 4) {
        schedule[i] =
            (chunk[j] << 24) | (chunk[j + 1] << 16) | (chunk[j + 2] << 8) | (chunk[j + 3]);
    }
}

static void sha256_add_chunk_padding(BYTE chunk[], short int chunk_position, size_t msg_len,
                                     bool append_bit) {
    uint64_t len = msg_len;
    short int shift = 56;

    /* appends 1 bit */
    if (append_bit) {
        chunk[chunk_position] = 1;
        chunk[chunk_position] <<= 7;
    }

    /* appends 64 bits containing msg_len at the end */
    for (short int i = 56; i < 64; i++) {
        chunk[i] = (BYTE)(len * 8 >> shift);
        shift -= 8;
    }
}

static void sha256_process_chunk(StruktsCtxSHA256* ctx, BYTE chunk[]) {
    WORD s0, s1, a, b, c, d, e, f, g, h, ch, tmp1, tmp2, maj;
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

    /* moves chunk (512 bits = 16 x 32 bits words) into schedule[0 .. 15] words */
    schedule_chunk(chunk, schedule);

    /* extend chunk to the rest of the schedule array */
    for (short int i = 16; i < 64; i++) {
        s0 = rotate_right(schedule[i - 15], 7) ^ rotate_right(schedule[i - 15], 18) ^
             schedule[i - 15] >> 3;

        s1 = rotate_right(schedule[i - 2], 17) ^ rotate_right(schedule[i - 2], 19) ^
             schedule[i - 2] >> 10;

        schedule[i] = schedule[i - 16] + s0 + schedule[i - 7] + s1;
    }

    /* SHA-256 compression part */
    for (short int i = 0; i < 64; i++) {
        s1 = rotate_right(e, 6) ^ rotate_right(e, 11) ^ rotate_right(e, 25);
        ch = (e & f) ^ ((~e) & g);
        tmp1 = h + s1 + ch + schedule_constants[i] + schedule[i];
        s0 = rotate_right(a, 2) ^ rotate_right(a, 13) ^ rotate_right(a, 22);
        maj = (a & b) ^ (a & c) ^ (b & c);
        tmp2 = s0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + tmp1;
        d = c;
        c = b;
        b = a;
        a = tmp1 + tmp2;
    }

    /* update sha256 state for next chunk */
    ctx->h0 += a;
    ctx->h1 += b;
    ctx->h2 += c;
    ctx->h3 += d;
    ctx->h4 += e;
    ctx->h5 += f;
    ctx->h6 += g;
    ctx->h7 += h;
}

static BYTE* sha256_build_digest(const StruktsCtxSHA256* sha256_ctx) {
    BYTE* hash = (BYTE*)calloc(32, sizeof(BYTE)); /* 256 bits digest */

    move_word(sha256_ctx->h0, hash, 0);
    move_word(sha256_ctx->h1, hash, 4);
    move_word(sha256_ctx->h2, hash, 8);
    move_word(sha256_ctx->h3, hash, 12);
    move_word(sha256_ctx->h4, hash, 16);
    move_word(sha256_ctx->h5, hash, 20);
    move_word(sha256_ctx->h6, hash, 24);
    move_word(sha256_ctx->h7, hash, 28);

    return hash;
}

/********************** PUBLIC FUNCTIONS **********************/
BYTE* strukts_crypto_sha256(const BYTE msg[], size_t msg_len) {
    StruktsCtxSHA256 sha256_ctx = strukts_ctx_sha256_new();
    short int chunk_position = 0; /* up to 64 (64 bytes = 512 bits) */
    BYTE chunk[64] = {0};         /* stores 512-bit chunks */

    /* processes all bytes of the original msg */
    for (size_t i = 0; i < msg_len; i++) {
        /* building the 512-bit chunk */
        chunk[chunk_position++] = msg[i];

        /* 512 bits (64 bytes) complete chunk has been created */
        if (chunk_position == 64) {
            chunk_position = 0;
            sha256_process_chunk(&sha256_ctx, chunk);
        }
    }

    sha256_prepare_chunk(chunk, chunk_position);

    /* an extra 512-bit block is required */
    if (chunk_position * 8 + 65 > 512) {
        /* finish current block with 1 extra bit and process it */
        chunk[chunk_position] = 1;
        chunk[chunk_position] <<= 7;
        sha256_process_chunk(&sha256_ctx, chunk);

        /* extra padding block creation */
        chunk_position = 0;

        sha256_prepare_chunk(chunk, chunk_position); /* cleans chunk before padding */
        sha256_add_chunk_padding(chunk, chunk_position, msg_len, false);
        sha256_process_chunk(&sha256_ctx, chunk);

        /* use final ctx to build the final 256-bit hash value */
        return sha256_build_digest(&sha256_ctx);
    }

    /* no new block required (complete chunk falls here too) */
    sha256_add_chunk_padding(chunk, chunk_position, msg_len, true);
    sha256_process_chunk(&sha256_ctx, chunk);

    return sha256_build_digest(&sha256_ctx);
}