/**
 * @file strukts_linkedlist.h
 *
 * @brief Module that contains linked lists implementations.
 *
 * A doubly linked list is a linear data struture that holds a single reference
 * to the next node of the list. To create one @see strukts_linkedlist_new.
 */

#ifndef STRUKTS_LINKEDLIST_H
#define STRUKTS_LINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

/**
 * A doubly linked list which can hold string values.
 */
typedef struct _StruktsLinkedList StruktsLinkedList;

/**
 * A node to be used in a doubly linked list.
 */
typedef struct _StruktsLinkedListNode StruktsLinkedListNode;

/**
 * Represents a search result in a linear data structure.
 */
typedef struct _StruktsLinearSearchResult StruktsLinearSearchResult;

struct _StruktsLinkedList {
    size_t size;

    StruktsLinkedListNode *first_node;
    StruktsLinkedListNode *last_node;
};

struct _StruktsLinkedListNode {
    const char *value; /* ptr is mutable, but the value content is not */

    StruktsLinkedListNode *next;
    StruktsLinkedListNode *previous;
};

struct _StruktsLinearSearchResult {
    bool found;
    size_t position;
};

/**
 * Allocates a new empty doubly linked list.
 *
 * @return a pointer to an empty doubly linked list.
 */
StruktsLinkedList *strukts_linkedlist_new();

/**
 * Allocates a new node and inserts it at the beginning (prepends) of the linked list.
 *
 * @param list is the linked list to have the new node added to its beginning.
 * @param value is a char pointer.
 *
 * @return true if a new node has been added to the beginning of the list; false otherwise.
 */
bool strukts_linkedlist_prepend(StruktsLinkedList *list, const char *value);

/**
 * Allocates a new node and inserts it at the end of the linked list.
 *
 * @param list is the linked list to have the new node added to its end.
 * @param value is a char pointer.
 *
 * @return true if a new node has been added to the end of the list; false otherwise.
 */
bool strukts_linkedlist_append(StruktsLinkedList *list, const char *value);

/**
 * Removes the first node from the beginning of a doubly linked list.
 *
 * @param list is the linked list which will have the first node removed.
 *
 * @return true if the first node has been removed; false otherwise.
 */
bool strukts_linkedlist_remove_first(StruktsLinkedList *list);

/**
 * Removes the first node from the beginning of a doubly linked list.
 *
 * @param list is the linked list which will have the first node removed.
 *
 * @return true if the first node has been removed; false otherwise.
 */
bool strukts_linkedlist_remove_last(StruktsLinkedList *list);

/**
 * Removes a node from the doubly linked list if its value is found.
 *
 * @param list is the linked list which will have the node removed.
 *
 * @return true if the node's value has been found and was removed; false otherwise.
 */
bool strukts_linkedlist_remove(StruktsLinkedList *list, const char *value);

/**
 * Traverses the linked list trying to find a value.
 *
 * @param list is the searched linked list.
 * @param value is the value to be searched in the linked list.
 *
 * @return a linear search result which contains whether the value was found
 * and its position.
 */
StruktsLinearSearchResult strukts_linkedlist_contains(StruktsLinkedList *list, const char *value);

/**
 * Deallocates all memory previously allocated by all nodes in the linked list.
 *
 * @param list is the searched linked list.
 */
void strukts_linkedlist_free(StruktsLinkedList *list);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_LINKEDLIST_H */