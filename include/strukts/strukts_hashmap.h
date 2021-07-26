/**
 * @file strukts_hashmap.h
 *
 * @brief Module that contains hashmap (hash tables/symbol tables) implementations.
 * To create a new empty hashmap, @see strukts_hashmap_new.
 *
 * The hashmap created by strukts_hashmap_new implements a hashmap using "separate
 * chaining" as the default way to handle hashing collisions.
 */

#ifndef STRUKTS_HASHMAP_H
#define STRUKTS_HASHMAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "strukts_linkedlist.h"

#define STRUKTS_HASHMAP_LOAD_FACTOR 0.7
#define STRUKTS_HASHMAP_INITIAL_BUCKET_SIZE 8

/**
 * Represents a hashmap (a.k.a as hash tables or symbol tables) using "separate chaining"
 * as the default way to deal with hashing collisions.
 */
typedef struct _StruktsHashmap StruktsHashmap;

struct _StruktsHashmap {
    size_t size;

    StruktsLinkedList* buckets[STRUKTS_HASHMAP_INITIAL_BUCKET_SIZE];
};

/**
 * Allocates a new hashmap with a starting size bucket to store keys and values.
 *
 * @return a pointer to an empty hashmap.
 */
StruktsHashmap* strukts_hashmap_new();

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_HASHMAP_H */