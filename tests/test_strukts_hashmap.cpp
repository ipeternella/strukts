#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "gtest/gtest.h"
#include "strukts_hashmap.h"

namespace {
    TEST(STRUKTS_HASHMAP_SUITE, SHOULD_ADD_KEY_VALUE_TO_HASHMAP) {
        // arrange
        const char key_1[10] = "k1";
        const char value_1[10] = "v1";
        const char* result;

        StruktsHashmap* dict = strukts_hashmap_new();

        // act
        bool added = strukts_hashmap_add(dict, key_1, value_1);

        // assert
        EXPECT_TRUE(added);
        EXPECT_EQ(dict->size, 1);
        EXPECT_EQ(dict->buckets_size, 8); /* starter value */

        // act - search for keys in the hash table
        result = strukts_hashmap_get(dict, "k1");

        // assert
        EXPECT_EQ(strcmp(result, "v1"), 0);
    }
}  // namespace
