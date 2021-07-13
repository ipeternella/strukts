#include "linked_lists.h"

#include <stdio.h>
#include <stdlib.h>

SinglyLinkedList *singly_linked_list_new() {
    SinglyLinkedList *list = (SinglyLinkedList *)malloc(sizeof(SinglyLinkedList));

    if (list == NULL) {
        printf("Unable to allocate memory for the linked list node.\n");
        exit(EXIT_FAILURE);
    }

    list->first_node = NULL;
    list->size = 0;

    return list;
}

void insert(int value, SinglyLinkedList *list) {
    // allocates a new node
    SinglyNode *new_node = (SinglyNode *)malloc(sizeof(SinglyNode));

    if (new_node == NULL) {
        printf("Unable to allocate memory for a singly node.\n");
        exit(EXIT_FAILURE);
    }

    // creates a new node pointing to the old first node
    new_node->value = value;
    new_node->next = list->first_node;

    // updates the first node
    list->first_node = new_node;
    list->size++;
}
