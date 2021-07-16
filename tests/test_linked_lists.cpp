#include "gtest/gtest.h"
#include "linked_lists.h"

namespace {
    TEST(LINKED_LISTS_SUITE, SHOULD_CREATE_AND_REMOVE_ITEMS_FROM_LINKED_LIST) {
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

        singly_linked_list_free(list);  // frees testing memory
    }

    TEST(LINKED_LISTS_SUITE, SHOULD_FIND_ELEMENT_IN_THE_LINKED_LIST) {
        // arrange
        SinglyLinkedList *list = singly_linked_list_new();
        insert_first(1, list);
        insert_first(5, list);
        insert_first(10, list);

        // act
        bool has_value = contains(5, list);

        // assert
        EXPECT_TRUE(has_value);

        // act
        has_value = contains(7, list);  // not in the list

        // assert
        EXPECT_FALSE(has_value);

        singly_linked_list_free(list);  // frees testing memory
    }
}  // namespace
