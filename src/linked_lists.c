#include <stdlib.h>
#include <stdio.h>
#include "linked_lists.h"

SinglyNode *singly_node_new(int value, SinglyNode *next)
{
    SinglyNode *node = (SinglyNode *)malloc(sizeof(SinglyNode));

    if (node == NULL)
    {
        printf("Unable to allocate memory for the singly node.\n");
        exit(EXIT_FAILURE);
    }

    node->value = value;
    node->next = next;

    return node;
}