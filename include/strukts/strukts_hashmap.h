/**
 * @file strukts_hashmap.h
 *
 * @brief Module that contains hash map (hash tables/symbol tables) implementations.
 * To create a new empty hashmap, @see strukts_hashmap_new.
 *
 * The hash map created by strukts_hashmap_new implements a hash map using "separate
 * chaining" as the default way to handle hashing collisions.
 */

#ifndef STRUKTS_HASHMAP_H
#define STRUKTS_HASHMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "strukts_linkedlist.h"

#ifdef DEBUG
#define STRUKTS_HASHMAP_INITIAL_CAPACITY 1
#else
#define STRUKTS_HASHMAP_INITIAL_CAPACITY 8
#endif

#define STRUKTS_HASHMAP_MAX_LOAD_FACTOR 0.7

/**
 * Represents a hash map (a.k.a as hash tables or symbol tables) using "separate chaining"
 * as the default way to deal with hashing collisions.
 */
typedef struct _StruktsHashmap StruktsHashmap;

struct _StruktsHashmap {
    size_t size;
    size_t capacity;             /* amount of available buckets */
    StruktsLinkedList** buckets; /* pointer to an array of lists pointers (buckets) */
};

/**
 * Allocates a new hash map with a starting size bucket to store keys and values.
 *
 * @return a pointer to an empty hashmap.
 */
StruktsHashmap* strukts_hashmap_new();

/**
 * Deallocates all memory previously allocated by the hashmap and its inner structures.
 *
 * @param hashmap is the hash map to deallocate.
 */
void strukts_hashmap_free(StruktsHashmap* hashmap);

/**
 * Adds a new key (and its value) to a hash map.
 *
 * @param hashmap is the address of a hashmap pointer.
 * @param key is a pointer to a string key.
 * @param value is a pointer to a string value.
 *
 * @return true if the key/value has been added to the hashmap. False, otherwise.
 */
bool strukts_hashmap_add(StruktsHashmap** hashmap, const char* key, const char* value);

/**
 * Searches for a given key in the hash map and returns its value if the key was found.
 *
 * @param hashmap is a pointer to hashmap.
 * @param key is a pointer to a string key which will be searched in the hash map.
 *
 * @return a pointer to the key's value if the key was found in the hash map; NULL, otherwise.
 */
char* strukts_hashmap_get(StruktsHashmap* hashmap, const char* key);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_HASHMAP_H */