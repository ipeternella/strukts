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

#endif /* __STRUKTS_LINKED_LISTS_H */