#include "gtest/gtest.h"
#include "linked_lists.h"

namespace {
    TEST(LINKED_LISTS_SUITE, CREATE_LINKED_LIST) {
        // arrange & act
        SinglyLinkedList *list = singly_linked_list_new();

        // assert
        EXPECT_EQ(list->size, 0);

        // act
        insert(10, list);
        insert(20, list);

        // assert
        EXPECT_EQ(list->first_node->value, 20);
        EXPECT_EQ(list->size, 2);
    }
}  // namespace
