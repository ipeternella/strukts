#include <memory.h>
#include <stdint.h>
#include <stdio.h>

#include "gtest/gtest.h"
#include "strukts_crypto.h"
#include "strukts_types.h"

#define BUILD_WORD(bytes, i) \
    (WORD)((bytes[i] << 24) | (bytes[i + 1] << 16) | (bytes[i + 2] << 8) | (bytes[i + 3]))

namespace
{
    TEST(STRUKTS_CRYPTO_SUITE, SHOULD_CREATE_SHA256_DIGEST_ONE_512_BLOCK)
    {
        /* arrange */
        BYTE nist_msg[] = {"abc"};
        size_t msg_len = 3; /* 3 chars = 3 bytes */

        /* act */
        BYTE* digest = strukts_crypto_sha256(nist_msg, msg_len);
        WORD digest_words[8] = {BUILD_WORD(digest, 0),  BUILD_WORD(digest, 4),
                                BUILD_WORD(digest, 8),  BUILD_WORD(digest, 12),
                                BUILD_WORD(digest, 16), BUILD_WORD(digest, 20),
                                BUILD_WORD(digest, 24), BUILD_WORD(digest, 28)};

        /*
         *  assert - expectation from NIST's SHA256 appendix B.1 (256 bit output - 1 block)
         *  https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2withchangenotice.pdf
         */
        WORD nist_expectation[8] = {0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223,
                                    0xb00361a3, 0x96177a9c, 0xb410ff61, 0xf20015ad};

        EXPECT_TRUE(memcmp(digest_words, nist_expectation, sizeof(digest_words)) == 0);

        free(digest);
    }

    TEST(STRUKTS_CRYPTO_SUITE, SHOULD_CREATE_SHA256_DIGEST_TWO_512_BLOCKS)
    {
        /* arrange */
        BYTE nist_msg[] = {"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"};
        size_t msg_len = 56; /* 56 chars = 56 bytes */

        /* act */
        BYTE* digest = strukts_crypto_sha256(nist_msg, msg_len);
        WORD digest_words[8] = {BUILD_WORD(digest, 0),  BUILD_WORD(digest, 4),
                                BUILD_WORD(digest, 8),  BUILD_WORD(digest, 12),
                                BUILD_WORD(digest, 16), BUILD_WORD(digest, 20),
                                BUILD_WORD(digest, 24), BUILD_WORD(digest, 28)};

        /*
         * assert - expectation from NIST's SHA256 appendix B.2 (256 bit output - 2 blocks)
         * https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2withchangenotice.pdf
         */
        WORD nist_expectation[8] = {0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039,
                                    0xa33ce459, 0x64ff2167, 0xf6ecedd4, 0x19db06c1};

        EXPECT_TRUE(memcmp(digest_words, nist_expectation, sizeof(digest_words)) == 0);

        free(digest);
    }
}  // namespace
