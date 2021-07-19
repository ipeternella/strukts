/**
 * @file strukts_linkedlist.h
 *
 * @brief Module that contains linked lists implementations.
 *
 * A singly linked list is a linear data struture that holds a single reference
 * to the next node of the list. To create one @see strukts_linkedlist_new.
 */

#ifndef STRUKTS_LINKEDLIST_H
#define STRUKTS_LINKEDLIST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/**
 * A node to be used in a singly linked list.
 */
typedef struct _StruktsSinglyNode StruktsSinglyNode;

/**
 * A linked list.
 */
typedef struct _StruktsLinkedList StruktsLinkedList;

struct _StruktsLinkedList {
    int size;
    StruktsSinglyNode *first_node;
};

struct _StruktsSinglyNode {
    int value;
    StruktsSinglyNode *next;
};

/**
 * Allocates a new empty singly linked list.
 *
 * @return a pointer to an empty linked list.
 */
StruktsLinkedList *strukts_linkedlist_new();

/**
 * Allocates a new node and inserts it at the beginning of a singly linked list.
 *
 * @param list is the linked list to have the new node added to its beginning.
 * @param value is the value which this node will hold in the list.
 */
void strukts_linkedlist_insert(StruktsLinkedList *list, int value);

/**
 * Removes the first node from the beginning of a singly linked list.
 *
 * @param list is the linked list which will have the first node removed.
 */
void strukts_linkedlist_remove(StruktsLinkedList *list);

/**
 * Traverses the linked list trying to find a value.
 *
 * @param list is the searched linked list.
 * @param value is the value to be searched in the linked list.
 *
 * @return true if the value is in the list; otherwise, false.
 */
bool strukts_linkedlist_contains(StruktsLinkedList *list, int value);

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