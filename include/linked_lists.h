/**
 * @file linked_lists.h
 *
 * @brief Linked lists implementations.
 *
 * A singly linked list is a linear data struture that holds a single reference
 * to the next node of the list. To create one @see singly_node_new.
 */

#ifndef __STRUKTS_LINKED_LISTS_H
#define __STRUKTS_LINKED_LISTS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/**
 * A node to be used in a singly linked list.
 */
typedef struct _SinglyNode SinglyNode;

/**
 * A singly linked list.
 */
typedef struct _SinglyLinkedList SinglyLinkedList;

struct _SinglyNode {
    int value;
    SinglyNode *next;
};

struct _SinglyLinkedList {
    int size;
    SinglyNode *first_node;
};

/**
 * Allocates a new empty singly linked list.
 *
 * @return a pointer to an empty linked list.
 */
SinglyLinkedList *singly_linked_list_new();

/**
 * Allocates a new node and inserts it at the beginning of a singly linked list.
 *
 * @param value is the value which this node will hold in the list.
 * @param list is the linked list to have the new node added to its beginning.
 */
void insert_first(int value, SinglyLinkedList *list);

/**
 * Removes the first node from the beginning of a singly linked list.
 *
 * @param list is the linked list which will have the first node removed.
 */
void remove_first(SinglyLinkedList *list);

/**
 * Traverses the linked list trying to find a value.
 *
 * @param value is the value to be searched in the linked list.
 * @param list is the searched linked list.
 * @return true if the value is in the list; otherwise, false.
 */
bool contains(int value, SinglyLinkedList *list);

/**
 * Deallocates all memory previously allocated by all nodes in the linked list.
 *
 * @param list is the searched linked list.
 */
void singly_linked_list_free(SinglyLinkedList *list);

#ifdef __cplusplus
}
#endif
#endif /* __STRUKTS_LINKED_LISTS_H */