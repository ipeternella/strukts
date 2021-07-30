#include "strukts_hashmap.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "strukts_hashing.h"
#include "strukts_linkedlist.h"

StruktsHashmap* strukts_hashmap_new() {
    StruktsHashmap* hashmap = (StruktsHashmap*)malloc(sizeof(StruktsHashmap));

    if (hashmap == NULL) return NULL;

    hashmap->buckets_size = STRUKTS_HASHMAP_INITIAL_BUCKETS_SIZE; /* amount of bucket slots */
    hashmap->size = 0;                                            /* amount of keys */

    /* initialize array of linked lists for separate chaining resolution */
    for (short int i = 0; i < STRUKTS_HASHMAP_INITIAL_BUCKETS_SIZE; i++) {
        StruktsLinkedList* list = strukts_linkedlist_new();

        if (list == NULL) return NULL;  // TODO: improve free code for this scenario

        hashmap->buckets[i] = list;
    }

    return hashmap;
}

// TODO: implement load factor checking, resizing and rehashing if needed
bool strukts_hashmap_add(StruktsHashmap* hashmap, const char* key, const char* value) {
    const uint8_t* key_bytes = (uint8_t*)key;
    const size_t key_len = strlen(key);
    const uint32_t seed = 0;

    StruktsLinkedList* list;

    /* modular hashing */
    uint32_t key_hash = strukts_murmur3_hash(key_bytes, key_len, seed);
    size_t bucket_hash = key_hash % hashmap->buckets_size;

    /* separate chaining for hashing collisions resolution */
    list = hashmap->buckets[bucket_hash];
    strukts_linkedlist_append(list, key, value);

    /* metadata updating */
    hashmap->size++;

    return true;
}

char* strukts_hashmap_get(StruktsHashmap* hashmap, const char* key) {
    const uint8_t* key_bytes = (uint8_t*)key;
    const size_t key_len = strlen(key);
    const uint32_t seed = 0;

    StruktsLinkedList* list;
    StruktsLinearSearchResult search_result;

    /* modular hashing */
    uint32_t key_hash = strukts_murmur3_hash(key_bytes, key_len, seed);
    size_t bucket_hash = key_hash % hashmap->buckets_size;

    list = hashmap->buckets[bucket_hash];
    search_result = strukts_linkedlist_find(list, key);

    if (!search_result.found) return NULL;

    return search_result.node->value;
}