#include "strukts_hashmap.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "strukts_hashing.h"
#include "strukts_linkedlist.h"

#ifdef DEBUG
#include "sfmalloc.h"
#define malloc sf_malloc
#define free sf_free
#endif

static bool is_rehashing_needed(StruktsHashmap* hashmap) {
    /* current load factor = hashmap->size / (float)hashmap->capacity */
    return hashmap->size / (float)hashmap->capacity >= STRUKTS_HASHMAP_MAX_LOAD_FACTOR;
}

static StruktsHashmap* strukts_hashmap_new_sized(size_t capacity) {
    if (capacity == 0) return NULL; /* impossible allocation */

    StruktsHashmap* hashmap = (StruktsHashmap*)malloc(sizeof(StruktsHashmap));

    if (hashmap == NULL) return NULL;

    /* these variables MUST have been set in case any malloc fails so that
     * strukts_hashmap_free() works fine */
    hashmap->capacity = capacity;
    hashmap->size = 0;

    /* allocates an array of pointers to buckets lists */
    hashmap->buckets = (StruktsLinkedList**)malloc(capacity * sizeof(StruktsLinkedList*));

    if (hashmap->buckets == NULL) {
        free(hashmap); /* ok to use bare free, nothing else has been allocated */

        return NULL;
    }

    /* initialize array of linked lists to NULL first (trading performance for readability) */
    for (size_t i = 0; i < capacity; i++) {
        hashmap->buckets[i] = NULL;
    }

    for (size_t i = 0; i < capacity; i++) {
        StruktsLinkedList* list = strukts_linkedlist_new();

        /* if an allocation error happens here, stop and free everything so far */
        if (list == NULL) {
            strukts_hashmap_free(hashmap); /* requires hashmap->capacity initialization */

            return NULL;
        }

        hashmap->buckets[i] = list;
    }

    return hashmap;
}

static StruktsHashmap* rehash(StruktsHashmap* old_hashmap) {
    StruktsLinkedList* list;
    StruktsLinkedListNode* current_node;
    StruktsHashmap* new_hashmap = strukts_hashmap_new_sized(2 * old_hashmap->capacity);

    if (new_hashmap == NULL) return NULL; /* reallocation has failed */

    /* rehash previous keys of the bucket lists into the new_hashmap */
    for (size_t i = 0; i < old_hashmap->size; i++) {
        list = old_hashmap->buckets[i];

        if (list == NULL || list->size < 1) continue; /* list must exists and not be empty */

        current_node = list->first_node;

        /* traverse each bucket's linked list of values */
        while (current_node != NULL) {
            /* rehash each key according to the new hashmap's capacity */
            bool added = strukts_hashmap_add(&new_hashmap, current_node->key, current_node->value);

            /* rehashing failed to add all keys: free any allocated memory and return */
            if (!added) {
                strukts_hashmap_free(new_hashmap);

                return NULL;
            }

            current_node = current_node->next;
        }
    }

    return new_hashmap;
}

StruktsHashmap* strukts_hashmap_new() {
    return strukts_hashmap_new_sized(STRUKTS_HASHMAP_INITIAL_CAPACITY);
}

void strukts_hashmap_free(StruktsHashmap* hashmap) {
    if (hashmap == NULL) return;

    StruktsLinkedList* list;

    /* deallocates all linked lists of the current hashmap used for collision resolution. Notice
     * that if hashmap != NULL, hashmap->capacity is ALWAYS initialized and hashmap->buckets TOO! */
    for (size_t i = 0; i < hashmap->capacity; i++) {
        list = hashmap->buckets[i];  // grab a pointer to a linked list

        /* asserts this bucket's index holds a list */
        if (list != NULL) strukts_linkedlist_free(list);
    }

    /* deallocate the array of bucket lists */
    free(hashmap->buckets);

    /* deallocate the current hashmap struct pointer*/
    free(hashmap);
}

bool strukts_hashmap_add(StruktsHashmap** hashmap_ptr, const char* key, const char* value) {
    if (is_rehashing_needed(*hashmap_ptr)) {
        /* reallocate bigger hash table and rehash all keys */
        StruktsHashmap* resized_hashmap = rehash(*hashmap_ptr);

        /* rehashing reallocation failed */
        if (resized_hashmap == NULL) return false;

        /* free old hashmap and point to the newly allocated hashmap */
        strukts_hashmap_free(*hashmap_ptr);
        *hashmap_ptr = resized_hashmap;
    }

    const uint8_t* key_bytes = (uint8_t*)key;
    const size_t key_len = strlen(key);
    const uint32_t seed = 0;

    StruktsHashmap* hashmap = *hashmap_ptr; /* possibly with newly allocated hashmap */

    /* modular hashing */
    uint32_t key_hash = strukts_murmur3_hash(key_bytes, key_len, seed);
    size_t bucket_hash = key_hash % hashmap->capacity;

    /* separate chaining for hashing collisions resolution */
    StruktsLinkedList* list = hashmap->buckets[bucket_hash];
    bool added = strukts_linkedlist_append(list, key, value);

    /* in the worst case scenario, hashmap is reallocated (bigger) and new addition failed */
    if (!added) return false;

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
    size_t bucket_hash = key_hash % hashmap->capacity;

    list = hashmap->buckets[bucket_hash];
    search_result = strukts_linkedlist_find(list, key);

    if (!search_result.found) return NULL;

    return search_result.node->value;
}