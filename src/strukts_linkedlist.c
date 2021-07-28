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

StruktsLinkedList* strukts_linkedlist_new() {
    StruktsLinkedList* list = (StruktsLinkedList*)malloc(sizeof(StruktsLinkedList));

    if (list == NULL) return NULL;

    /* initial state */
    list->size = 0;
    list->first_node = NULL;
    list->last_node = NULL;

    return list;
}

StruktsLinkedListNode* strukts_linkedlistnode_new(const char* key, const char* value) {
    StruktsLinkedListNode* new_node = (StruktsLinkedListNode*)malloc(sizeof(StruktsLinkedListNode));

    if (new_node == NULL) return NULL;

    /* initialize new node */
    new_node->next = NULL;
    new_node->previous = NULL;
    new_node->value = value;
    new_node->key = key;

    return new_node;
}

bool strukts_linkedlist_prepend(StruktsLinkedList* list, const char* key, const char* value) {
    StruktsLinkedListNode* new_node = strukts_linkedlistnode_new(key, value);

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

bool strukts_linkedlist_append(StruktsLinkedList* list, const char* key, const char* value) {
    StruktsLinkedListNode* new_node = strukts_linkedlistnode_new(key, value);

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

bool strukts_linkedlist_remove_first(StruktsLinkedList* list) {
    if (list->size == 0) return false;

    if (list->size == 1) {
        free(list->first_node);

        list->first_node = NULL;
        list->last_node = NULL;
        list->size--;

        return true;
    }

    /* lists bigger than one */
    StruktsLinkedListNode* old_first_node = list->first_node;
    StruktsLinkedListNode* new_first_node = old_first_node->next;

    new_first_node->previous = NULL;
    list->first_node = new_first_node;
    list->size--;

    free(old_first_node);

    return true;
}

bool strukts_linkedlist_remove_last(StruktsLinkedList* list) {
    if (list->size == 0) return false;

    if (list->size == 1) {
        free(list->first_node);

        list->first_node = NULL;
        list->last_node = NULL;
        list->size--;

        return true;
    }

    /* lists bigger than one */
    StruktsLinkedListNode* old_last_node = list->last_node;
    StruktsLinkedListNode* new_last_node = old_last_node->previous;

    new_last_node->next = NULL;
    list->last_node = new_last_node;
    list->size--;

    free(old_last_node);

    return true;
}

bool strukts_linkedlist_remove(StruktsLinkedList* list, const char* key) {
    StruktsLinearSearchResult search_result = strukts_linkedlist_contains(list, key);

    if (!search_result.found) return false;
    if (search_result.position == 0) return strukts_linkedlist_remove_first(list);
    if (search_result.position == list->size - 1) return strukts_linkedlist_remove_last(list);

    /* guaranteed to be in the middle of the list */
    StruktsLinkedListNode* current_node = list->first_node;

    while (current_node != NULL) {
        if (strcmp(current_node->key, key) == 0) break;

        current_node = current_node->next;
    }

    /* disconnect node from list */
    current_node->previous->next = current_node->next;
    current_node->next->previous = current_node->previous;
    list->size--;

    free(current_node);

    return true;
}

StruktsLinearSearchResult strukts_linkedlist_contains(StruktsLinkedList* list, const char* key) {
    StruktsLinkedListNode* current_node = list->first_node;
    StruktsLinearSearchResult result = {false, 0};
    size_t position = 0;

    while (current_node != NULL) {
        if (strcmp(current_node->key, key) == 0) {
            result.found = true;
            result.position = position;
            result.value = current_node->value;

            break;
        }

        current_node = current_node->next;
        position++;
    }

    return result;
}

void strukts_linkedlist_free(StruktsLinkedList* list) {
    StruktsLinkedListNode* current_node = list->first_node;

    while (current_node != NULL) {
        StruktsLinkedListNode* next_node = current_node->next;

        /* deallocates each node of the list */
        free(current_node);

        current_node = next_node;
    }

    /* deallocates the list pointer */
    free(list);
}