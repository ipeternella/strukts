#include <stdlib.h>
#include <stdio.h>

#include "linked_lists.h"

int main()
{
    SinglyNode *first_node = singly_node_new(5, NULL);

    printf("First node: %d", first_node->value);

    return EXIT_SUCCESS;
}
