#include "linked_lists.h"

#include <stdio.h>
#include <stdlib.h>

SinglyLinkedList *singly_linked_list_new() {
    SinglyLinkedList *list = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));

    if (list == NULL) return NULL;

    list->first_node = NULL;
    list->size = 0;

    return list;
}

void insert_first(int value, SinglyLinkedList *list) {
    // allocates a new node
    SinglyNode *new_node = (SinglyNode *)malloc(sizeof(SinglyNode));

    if (new_node == NULL) return;

    // creates a new node pointing to the old first node
    new_node->value = value;
    new_node->next = list->first_node;

    // updates the first node
    list->first_node = new_node;
    list->size++;
}

void remove_first(SinglyLinkedList *list) {
    if (list->size == 1) {
        SinglyNode *node = list->first_node;

        list->first_node = NULL;
        list->size = 0;

        free(node);
    } else if (list->size > 1) {
        SinglyNode *first = list->first_node;
        SinglyNode *second = first->next;

        list->first_node = second;
        list->size--;

        free(first);
    }
}