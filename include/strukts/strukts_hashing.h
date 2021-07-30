/**
 * @file strukts_hashing.h
 *
 * @brief Module that contains non-crypto hash functions implementations.
 *
 * Non-crypto hashes are hash functions suitable for general hash-based lookup
 * (dictionaries, symbol tables, etc.). Unlike crypto hashes, they're NOT designed
 * for preimage resistance, i.e., they are not hard to reverse by an adversary.
 *
 * The original MurMur hash algorithm was designed by Austin Appleby in 2008.
 */

#ifndef STRUKTS_HASHING_H
#define STRUKTS_HASHING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Hashes a key using the MurMur3 hashing algorithm to produce a 32-bit sized hash.
 *
 * @param key is a pointer to an array of bytes (of 8 bits) to be hashed.
 * @param key_len is the amount of bytes that key points to (size of the bytes array).
 * @param seed is a random seed used by the algorithm.
 *
 * @return a fixed hash value of the key of 32 bits.
 */
uint32_t strukts_murmur3_hash(const uint8_t* key, size_t key_len, uint32_t seed);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_HASHING_H */