#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "gtest/gtest.h"
#include "strukts_hashing.h"

namespace {
    TEST(STRUKTS_HASHING_SUITE, SHOULD_32BIT_MURMUR3_HASH_STRING_WITH_5_BYTES) {
        // arrange
        const char str[10] = "abcde";  // literal str: {'a', 'b', 'c', 'd', 'e', '\0'};
        const uint8_t *str_bytes = (uint8_t *)str;
        size_t str_len = strlen(str);
        const int seed = 0;

        // act
        uint32_t hash = murmur3_hash(str_bytes, str_len, seed);

        // assert
        EXPECT_EQ(hash, -392455434);  // expectation from python's lib mmh3
    }

    TEST(STRUKTS_HASHING_SUITE, SHOULD_32BIT_MURMUR3_HASH_STRING_WITH_2_BYTES) {
        // arrange
        const char str[10] = "ab";
        const uint8_t *str_bytes = (uint8_t *)str;
        size_t str_len = strlen(str);
        const int seed = 5;

        // act
        uint32_t hash = murmur3_hash(str_bytes, str_len, seed);

        // assert
        EXPECT_EQ(hash, 810406479);  // expectation from python's lib mmh3
    }

    TEST(STRUKTS_HASHING_SUITE, SHOULD_32BIT_MURMUR3_HASH_STRING_WITH_22_BYTES) {
        // arrange
        const char str[50] = "some really nice long key";
        const uint8_t *str_bytes = (uint8_t *)str;
        size_t str_len = strlen(str);
        uint32_t seed = 10;

        // act
        uint32_t hash = murmur3_hash(str_bytes, str_len, seed);

        // assert
        EXPECT_EQ(hash, -464589223);  // expectation from python's lib mmh3
    }
}  // namespace
