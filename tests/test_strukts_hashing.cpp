#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "gtest/gtest.h"
#include "strukts_hashing.h"
#include "strukts_types.h"

namespace
{
    TEST(STRUKTS_HASHING_SUITE, SHOULD_32BIT_MURMUR3_HASH_STRING_WITH_5_BYTES)
    {
        /* arrange */
        const char str[10] = "abcde";  // literal str: {'a', 'b', 'c', 'd', 'e', '\0'};
        const BYTE* str_bytes = (BYTE*)str;
        const WORD seed = 0;
        size_t str_len = strlen(str);

        /* act */
        WORD hash = strukts_murmur3_hash(str_bytes, str_len, seed);

        /* assert */
        EXPECT_EQ(hash, -392455434);  // expectation from python's lib mmh3
    }

    TEST(STRUKTS_HASHING_SUITE, SHOULD_32BIT_MURMUR3_HASH_STRING_WITH_2_BYTES)
    {
        /* arrange */
        const char str[10] = "ab";
        const BYTE* str_bytes = (BYTE*)str;
        const WORD seed = 5;
        size_t str_len = strlen(str);

        /* act */
        WORD hash = strukts_murmur3_hash(str_bytes, str_len, seed);

        /* assert */
        EXPECT_EQ(hash, 810406479);  // expectation from python's lib mmh3
    }

    TEST(STRUKTS_HASHING_SUITE, SHOULD_32BIT_MURMUR3_HASH_STRING_WITH_22_BYTES)
    {
        /* arrange */
        const char str[50] = "some really nice long key";
        const BYTE* str_bytes = (BYTE*)str;
        const WORD seed = 10;
        size_t str_len = strlen(str);

        /* act */
        WORD hash = strukts_murmur3_hash(str_bytes, str_len, seed);

        /* assert */
        EXPECT_EQ(hash, -464589223);  // expectation from python's lib mmh3
    }
}  // namespace
