/**
 * @file strukts_crypto.h
 *
 * @brief Module that contains crypto hash functions implementations such as the NIST's
 * SHA-256 from the SHA-2 family based on Merkle-Damgard's construction using Davies-Meyer's
 * structure.
 *
 * Unlike non-crypto hashes, crypto ones are designed for security characteristics
 * such as preimage resistance (hard to be reversed by an adversary), etc.
 */

#ifndef STRUKTS_CRYPTO_H
#define STRUKTS_CRYPTO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include "strukts_types.h"

/**
 * Represents the state/context of the SHA256 hashing algorithm.
 */
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

/**
 * Hashes a message using the SHA-256 crypto-hashing function from the SHA-2 family.
 *
 * @param msg is the byte array of the message
 * @param msg_len is the amount of bytes in the message
 *
 * @return the digest (hash value) as a pointer to a byte array of 256 bits (array of 32 indexes).
 */
BYTE* strukts_crypto_sha256(const BYTE msg[], size_t msg_len);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_CRYPTO_H */