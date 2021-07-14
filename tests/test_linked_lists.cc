#include "gtest/gtest.h"
#include "linked_lists.h"

namespace {
    TEST(LINKED_LISTS_SUITE, CREATE_LINKED_LIST) {
        // arrange & act
        SinglyLinkedList *list = singly_linked_list_new();

        // assert
        EXPECT_EQ(list->size, 0);

        // act
        insert_first(10, list);
        insert_first(20, list);

        // assert
        EXPECT_EQ(list->first_node->value, 20);
        EXPECT_EQ(list->size, 2);

        // act
        remove_first(list);

        // assert
        EXPECT_EQ(list->size, 1);
        EXPECT_EQ(list->first_node->value, 10);

        // act
        remove_first(list);

        // assert
        EXPECT_EQ(list->size, 0);
        EXPECT_TRUE(list->first_node == nullptr);

        // act (empty list)
        remove_first(list);

        // assert
        EXPECT_EQ(list->size, 0);
        EXPECT_TRUE(list->first_node == nullptr);
    }
}  // namespace
