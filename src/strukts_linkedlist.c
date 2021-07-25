#include "strukts_linkedlist.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sfmalloc.h"

#ifdef DEBUG
#define malloc sf_malloc
#define free sf_free
#endif

StruktsLinkedList *strukts_linkedlist_new() {
    StruktsLinkedList *list = (StruktsLinkedList *)malloc(sizeof(StruktsLinkedList));

    if (list == NULL) return NULL;

    /* initial state */
    list->size = 0;
    list->first_node = NULL;
    list->last_node = NULL;

    return list;
}

StruktsLinkedListNode *strukts_linkedlistnode_new(const char *value) {
    StruktsLinkedListNode *new_node =
        (StruktsLinkedListNode *)malloc(sizeof(StruktsLinkedListNode));

    if (new_node == NULL) return NULL;

    /* initialize new node */
    new_node->next = NULL;
    new_node->previous = NULL;
    new_node->value = value;

    return new_node;
}

bool strukts_linkedlist_prepend(StruktsLinkedList *list, const char *value) {
    StruktsLinkedListNode *new_node = strukts_linkedlistnode_new(value);

    if (new_node == NULL) return false;

    if (list->size == 0) {
        list->first_node = new_node;
        list->last_node = new_node;
    } else {
        new_node->next = list->first_node;
        list->first_node->previous = new_node;
        list->first_node = new_node;
    }
    list->size++;

    return true;
}

bool strukts_linkedlist_append(StruktsLinkedList *list, const char *value) {
    StruktsLinkedListNode *new_node = strukts_linkedlistnode_new(value);

    if (new_node == NULL) return false;

    if (list->size == 0) {
        list->first_node = new_node;
        list->last_node = new_node;
        list->size++;

        return true;
    }

    new_node->previous = list->last_node;
    list->last_node->next = new_node;  // !
    list->last_node = new_node;
    list->size++;

    return true;
}

bool strukts_linkedlist_remove_first(StruktsLinkedList *list) {
    if (list->size == 0) return false;

    if (list->size == 1) {
        list->first_node = NULL;
        list->last_node = NULL;
        list->size--;

        return true;
    }

    /* lists bigger than one */
    StruktsLinkedListNode *old_first_node = list->first_node;
    StruktsLinkedListNode *new_first_node = old_first_node->next;

    new_first_node->previous = NULL;
    list->first_node = new_first_node;
    list->size--;

    free(old_first_node);

    return true;
}

bool strukts_linkedlist_contains(StruktsLinkedList *list, const char *value) {
    StruktsLinkedListNode *current_node = list->first_node;

    while (current_node != NULL) {
        if (strcmp(current_node->value, value) == 0) return true;

        current_node = current_node->next; /* may be NULL */
    }

    return false;
}

void strukts_linkedlist_free(StruktsLinkedList *list) {
    StruktsLinkedListNode *current_node = list->first_node;

    while (current_node != NULL) {
        StruktsLinkedListNode *next_node = current_node->next;

        /* deallocates each node of the list */
        free(current_node);

        current_node = next_node;
    }

    /* deallocates the list pointer */
    free(list);
}