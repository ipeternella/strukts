/**
 * @file strukts_linkedlist.h
 *
 * @brief Module that contains linked lists implementations.
 *
 * A doubly linked list is a linear data struture in which each node holds
 * a reference to the previous and next nodes in the list. To create one
 * @see strukts_linkedlist_new.
 */

#ifndef STRUKTS_LINKEDLIST_H
#define STRUKTS_LINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

/**
 * A node to be used in a doubly linked list.
 */
typedef struct _StruktsLinkedListNode StruktsLinkedListNode;

struct _StruktsLinkedListNode {
    const char* key; /* 'id' for the values, should not be mutated */
    char* value;
    StruktsLinkedListNode* next;
    StruktsLinkedListNode* previous;
};

/**
 * A doubly linked list which can hold string values.
 */
typedef struct _StruktsLinkedList StruktsLinkedList;

struct _StruktsLinkedList {
    size_t size;
    StruktsLinkedListNode* first_node;
    StruktsLinkedListNode* last_node;
};

/**
 * Represents a search result in a linear data structure.
 */
typedef struct _StruktsLinearSearchResult StruktsLinearSearchResult;

struct _StruktsLinearSearchResult {
    bool found;
    size_t position;
    StruktsLinkedListNode* node;
};

/**
 * Allocates a new empty doubly linked list.
 *
 * @return a pointer to an empty doubly linked list.
 */
StruktsLinkedList* strukts_linkedlist_new();

/**
 * Deallocates all memory previously allocated by all nodes in the linked list.
 *
 * @param list is the linked list to deallocate.
 */
void strukts_linkedlist_free(StruktsLinkedList* list);

/**
 * Allocates a new node and inserts it at the beginning (prepends) of the linked list. For adding
 * a node whose key is equal to its value, use the macro strukts_linkedlist_prependkv(list, key).
 * This function does not modify the contents of key and value pointers.
 *
 * @param list is the linked list to have the new node added to its beginning.
 * @param key is the key used to identify this node.
 * @param value is the value associated with the key (satellite data).
 *
 * @return true if a new node has been added to the beginning of the list; false otherwise.
 */
bool strukts_linkedlist_prepend(StruktsLinkedList* list, const char* key, char* value);

/**
 * Allocates a new node and inserts it at the end of the linked list. For adding a node whose
 * key is equal to its value, use the macro strukts_linkedlist_appendkv(list, key).
 * This function does not modify the contents of key and value pointers.
 *
 * @param list is the linked list to have the new node added to its end.
 * @param key is the key used to identify this node.
 * @param value is the value associated with the key (satellite data).
 *
 * @return true if a new node has been added to the end of the list; false otherwise.
 */
bool strukts_linkedlist_append(StruktsLinkedList* list, const char* key, char* value);

/**
 * Removes the first node from the beginning of a doubly linked list.
 *
 * @param list is the linked list which will have the first node removed.
 *
 * @return true if the first node has been removed; false otherwise.
 */
bool strukts_linkedlist_remove_first(StruktsLinkedList* list);

/**
 * Removes the first node from the beginning of a doubly linked list.
 *
 * @param list is the linked list which will have the first node removed.
 *
 * @return true if the first node has been removed; false otherwise.
 */
bool strukts_linkedlist_remove_last(StruktsLinkedList* list);

/**
 * Removes a node from the doubly linked list if its value is found.
 *
 * @param list is the linked list which will have the node removed.
 *
 * @return true if the node's value has been found and was removed; false otherwise.
 */
bool strukts_linkedlist_remove(StruktsLinkedList* list, const char* key);

/**
 * Traverses the linked list trying to find a value by its key.
 *
 * @param list is the searched linked list.
 * @param key is the key to be searched in the linked list.
 *
 * @return a linear search result which contains whether the value was found
 * and its position.
 */
StruktsLinearSearchResult strukts_linkedlist_find(StruktsLinkedList* list, const char* key);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_LINKEDLIST_H */