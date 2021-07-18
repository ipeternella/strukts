#include "linked_lists.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sfmalloc.h"

#define malloc sf_malloc
#define free sf_free

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

bool contains(int value, SinglyLinkedList *list) {
    if (list->size == 0) return NULL;

    SinglyNode *current_node = list->first_node;

    while (current_node != NULL) {
        if (current_node->value == value) return true;

        current_node = current_node->next;  // may be NULL
    }

    return false;
}

void singly_linked_list_free(SinglyLinkedList *list) {
    SinglyNode *current_node = list->first_node;

    while (current_node != NULL) {
        SinglyNode *next_node = current_node->next;  // becomes NULL if current_node is the last one

        // deallocate current_node's heap memory
        free(current_node);

        current_node = next_node;
    }

    free(list);
}