#include "gtest/gtest.h"
#include "strukts_linkedlist.h"

namespace {
    TEST(STRUKTS_LINKEDLISTS_SUITE, SHOULD_CREATE_AND_REMOVE_ITEMS_FROM_LINKED_LIST) {
        // arrange & act
        StruktsLinkedList *list = strukts_linkedlist_new();

        // assert
        EXPECT_EQ(list->size, 0);

        // act
        strukts_linkedlist_insert(list, 10);
        strukts_linkedlist_insert(list, 20);

        // assert
        EXPECT_EQ(list->first_node->value, 20);
        EXPECT_EQ(list->size, 2);

        // act
        strukts_linkedlist_remove(list);

        // assert
        EXPECT_EQ(list->size, 1);
        EXPECT_EQ(list->first_node->value, 10);

        // act
        strukts_linkedlist_remove(list);

        // assert
        EXPECT_EQ(list->size, 0);
        EXPECT_TRUE(list->first_node == nullptr);

        // act (empty list)
        strukts_linkedlist_remove(list);

        // assert
        EXPECT_EQ(list->size, 0);
        EXPECT_TRUE(list->first_node == nullptr);

        strukts_linkedlist_free(list);  // frees testing memory
    }

    TEST(STRUKTS_LINKEDLISTS_SUITE, SHOULD_FIND_ELEMENT_IN_THE_LINKED_LIST) {
        // arrange
        StruktsLinkedList *list = strukts_linkedlist_new();

        strukts_linkedlist_insert(list, 1);
        strukts_linkedlist_insert(list, 5);
        strukts_linkedlist_insert(list, 10);

        // act
        bool has_value = strukts_linkedlist_contains(list, 5);

        // assert
        EXPECT_TRUE(has_value);

        // act
        has_value = strukts_linkedlist_contains(list, 7);  // not in the list

        // assert
        EXPECT_FALSE(has_value);

        strukts_linkedlist_free(list);  // frees testing memory
    }
}  // namespace
