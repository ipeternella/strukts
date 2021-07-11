#include <stdlib.h>
#include <stdio.h>

#include "linked_lists.h"

int main()
{
    SinglyLinkedList *list = singly_linked_list_new();

    printf("size: %d\n", list->size);

    insert(10, list);

    printf("size: %d, first_value: %d\n", list->size, list->first_node->value);

    return EXIT_SUCCESS;
}
