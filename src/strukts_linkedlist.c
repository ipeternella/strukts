#include "strukts_linkedlist.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sfmalloc.h"

#define malloc sf_malloc
#define free sf_free

StruktsLinkedList *strukts_linkedlist_new() {
    StruktsLinkedList *list = (StruktsLinkedList *)malloc(sizeof(StruktsLinkedList));

    if (list == NULL) return NULL;

    /* initial state */
    list->first_node = NULL;
    list->size = 0;

    return list;
}

void strukts_linkedlist_insert(StruktsLinkedList *list, int value) {
    StruktsSinglyNode *new_node = (StruktsSinglyNode *)malloc(sizeof(StruktsSinglyNode));

    if (new_node == NULL) return;

    /* creates a new node pointing to the old first node */
    new_node->value = value;
    new_node->next = list->first_node;

    /* updates the first node */
    list->first_node = new_node;
    list->size++;
}

void strukts_linkedlist_remove(StruktsLinkedList *list) {
    if (list->size == 1) {
        StruktsSinglyNode *node = list->first_node;

        list->first_node = NULL;
        list->size = 0;

        free(node);
    } else if (list->size > 1) {
        StruktsSinglyNode *first = list->first_node;
        StruktsSinglyNode *second = first->next;

        list->first_node = second;
        list->size--;

        free(first);
    }
}

bool strukts_linkedlist_contains(StruktsLinkedList *list, int value) {
    if (list->size == 0) return NULL;

    StruktsSinglyNode *current_node = list->first_node;

    while (current_node != NULL) {
        if (current_node->value == value) return true;

        current_node = current_node->next;  // may be NULL
    }

    return false;
}

void strukts_linkedlist_free(StruktsLinkedList *list) {
    StruktsSinglyNode *current_node = list->first_node;

    while (current_node != NULL) {
        StruktsSinglyNode *next_node = current_node->next;

        /* deallocates each node of the list */
        free(current_node);

        current_node = next_node;
    }

    /* deallocates the list pointer */
    free(list);
}