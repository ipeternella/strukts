/**
 * @file strukts_crypto.h
 *
 * @brief Module that contains crypto hash functions implementations such as the NIST's
 * SHA-256 from the SHA-2 family based on Merkle-Damgard's construction using Davies-Meyer's
 * structure.
 *
 * Unlike non-crypto hashes, crypto ones are designed for security characteristics
 * such as preimage resistance (hard to be reversed by an adversary), etc.
 *
 * Observations:
 *
 * The SHA-256 algorithm can be found on NIST's page (along with some test/validation data):
 * https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf
 *
 * This modest SHA-256's implementation was improved based on Brad Conte's implementation:
 * https://github.com/B-Con/crypto-algorithms/blob/master/sha256.c
 */

#ifndef STRUKTS_CRYPTO_H
#define STRUKTS_CRYPTO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#include "strukts_types.h"

/**
 * Hashes a message using the SHA-256 crypto-hashing function from the SHA-2 family.
 *
 * @param msg is the byte array of the message
 * @param msg_len is the amount of bytes in the message
 *
 * @return the digest (hash value) as a calloc'd pointer to a byte array of 256 bits whose
 * length is 32.
 */
BYTE* strukts_crypto_sha256(const BYTE msg[], size_t msg_len);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_CRYPTO_H */