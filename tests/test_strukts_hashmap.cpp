#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "gtest/gtest.h"
#include "strukts_hashmap.h"

namespace {
    TEST(STRUKTS_HASHMAP_SUITE, SHOULD_ADD_KEY_VALUE_TO_HASHMAP_WITH_REHASHING) {
        // arrange
        char* value;
        bool added = false;
        StruktsHashmap* dict = strukts_hashmap_new();

        // act - add key/value and search the for the key in the hashmap
        added = strukts_hashmap_add(&dict, "k1", "v1");
        value = strukts_hashmap_get(dict, "k1");

        // assert
        EXPECT_TRUE(added);
        EXPECT_EQ(dict->size, 1);
        EXPECT_EQ(dict->capacity, 1); /* hashmap initial value in DEBUG mode */
        EXPECT_EQ(strcmp(value, "v1"), 0);

        // act - adding new key should rehash keys from capacity 1 to 2^1
        added = strukts_hashmap_add(&dict, "k2", "v2");
        value = strukts_hashmap_get(dict, "k2");

        // assert
        EXPECT_TRUE(added);
        EXPECT_EQ(dict->size, 2);
        EXPECT_EQ(dict->capacity, 2);
        EXPECT_EQ(strcmp(value, "v2"), 0);

        // act - adding new key should rehash keys from capacity 2ˆ1 to 2^2
        added = strukts_hashmap_add(&dict, "k3", "v3");
        value = strukts_hashmap_get(dict, "k3");

        // assert
        EXPECT_TRUE(added);
        EXPECT_EQ(dict->size, 3);
        EXPECT_EQ(dict->capacity, 4);
        EXPECT_EQ(strcmp(value, "v3"), 0);

        // act - adding new key should rehash keys from capacity 2^2 to 2^3
        added = strukts_hashmap_add(&dict, "k4", "v4");
        value = strukts_hashmap_get(dict, "k4");

        // assert
        EXPECT_TRUE(added);
        EXPECT_EQ(dict->size, 4);
        EXPECT_EQ(dict->capacity, 8);
        EXPECT_EQ(strcmp(value, "v4"), 0);

        // act - adding new key for current load factor should NOT trigger new rehashing
        added = strukts_hashmap_add(&dict, "k5", "v5");
        value = strukts_hashmap_get(dict, "k5");

        // assert
        EXPECT_TRUE(added);
        EXPECT_EQ(dict->size, 5);
        EXPECT_EQ(dict->capacity, 8);  // NO rehashing (same capacity)
        EXPECT_EQ(strcmp(value, "v5"), 0);

        strukts_hashmap_free(dict);
    }
}  // namespace
