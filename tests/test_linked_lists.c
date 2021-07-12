#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_runner.h"
#include "linked_lists.h"

void test_should_create_singly_linked_list_with_two_nodes()
{
    // arrange & act
    SinglyLinkedList *list = singly_linked_list_new();

    // assert
    assert(list->size == 0);

    // act
    insert(10, list);
    insert(20, list);

    // assert
    assert(list->first_node->value == 20);
    assert(list->size == 2);
}

static UnitTest tests[] = {test_should_create_singly_linked_list_with_two_nodes, NULL};

int main()
{
    run(tests);

    return EXIT_SUCCESS;
}