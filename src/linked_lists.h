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

struct _SinglyNode
{
    int value;
    SinglyNode *next;
};

/**
 * Allocates a new node to be used in a singly linked list.
 * 
 * @param value is the value which this node will hold in the list.
 * @return a pointer to a new node or NULL if allocation was not successful.
 */
SinglyNode *singly_node_new(int value, SinglyNode *next);

#endif /* __STRUKTS_LINKED_LISTS_H */