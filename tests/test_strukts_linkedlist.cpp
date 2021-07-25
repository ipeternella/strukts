#include <string.h>

#include "gtest/gtest.h"
#include "strukts_linkedlist.h"

namespace {
    TEST(STRUKTS_LINKEDLISTS_SUITE, SHOULD_CREATE_AND_REMOVE_ITEMS_FROM_DOUBLY_LINKED_LIST) {
        // arrange & act
        StruktsLinkedList *list = strukts_linkedlist_new();
        const char *first = "10";
        const char *second = "20";
        const char *third = "30";
        const char *fourth = "40";
        const char *fifth = "50";

        // assert
        EXPECT_EQ(list->size, 0);

        // act - add elements to the beginning
        strukts_linkedlist_prepend(list, first);
        strukts_linkedlist_prepend(list, second);
        strukts_linkedlist_prepend(list, third);

        // assert - ["30", "20", "10"]
        EXPECT_EQ(list->size, 3);
        EXPECT_EQ(strcmp(list->first_node->value, third), 0);
        EXPECT_EQ(strcmp(list->last_node->value, first), 0);

        // act - add elements to the end
        strukts_linkedlist_append(list, fourth);
        strukts_linkedlist_append(list, fifth);

        // assert - ["30", "20", "10", "40", "50"]
        EXPECT_EQ(list->size, 5);
        EXPECT_EQ(strcmp(list->first_node->value, third), 0);
        EXPECT_EQ(strcmp(list->last_node->value, fifth), 0);

        // act - remove first element
        strukts_linkedlist_remove_first(list);

        // assert - ["20", "10", "40", "50"]
        EXPECT_EQ(list->size, 4);
        EXPECT_EQ(strcmp(list->first_node->value, second), 0);
        EXPECT_EQ(strcmp(list->last_node->value, fifth), 0);

        // act - remove last element
        strukts_linkedlist_remove_last(list);

        // assert - ["20", "10", "40"]
        EXPECT_EQ(list->size, 3);
        EXPECT_EQ(strcmp(list->first_node->value, second), 0);
        EXPECT_EQ(strcmp(list->last_node->value, fourth), 0);

        strukts_linkedlist_free(list);
    }

    TEST(STRUKTS_LINKEDLISTS_SUITE, SHOULD_FIND_ELEMENT_IN_THE_LINKED_LIST) {
        // arrange - create list ["1", "2", "3"]
        StruktsLinkedList *list = strukts_linkedlist_new();
        StruktsLinearSearchResult search_result;

        const char *one = "1";
        const char *two = "2";
        const char *three = "3";
        const char *not_in_list = "7";

        strukts_linkedlist_append(list, one);
        strukts_linkedlist_append(list, two);
        strukts_linkedlist_append(list, three);

        // act - search in ["1", "2", "3"]
        search_result = strukts_linkedlist_contains(list, one);

        // assert
        EXPECT_TRUE(search_result.found);
        EXPECT_EQ(search_result.position, 0);

        // act
        search_result = strukts_linkedlist_contains(list, two);

        // assert
        EXPECT_TRUE(search_result.found);
        EXPECT_EQ(search_result.position, 1);

        // act
        search_result = strukts_linkedlist_contains(list, three);

        // assert
        EXPECT_TRUE(search_result.found);
        EXPECT_EQ(search_result.position, 2);

        // act
        search_result = strukts_linkedlist_contains(list, not_in_list);  // not in the list

        // assert
        EXPECT_FALSE(search_result.found);  // not found
        EXPECT_EQ(search_result.position, 0);

        // act - remove last element and search for it - ["1", "2"]
        strukts_linkedlist_remove_last(list);
        search_result = strukts_linkedlist_contains(list, three);

        // assert
        EXPECT_FALSE(search_result.found);  // not found
        EXPECT_EQ(search_result.position, 0);

        strukts_linkedlist_free(list);  // frees testing memory
    }

    TEST(STRUKTS_LINKEDLISTS_SUITE, SHOULD_REMOVE_ELEMENTS_FROM_LINKEDLIST) {
        // arrange - create list ["1", "2", "3"]
        StruktsLinkedList *list = strukts_linkedlist_new();
        bool result;

        const char *one = "1";
        const char *two = "2";
        const char *three = "3";

        strukts_linkedlist_append(list, one);
        strukts_linkedlist_append(list, two);
        strukts_linkedlist_append(list, three);

        // act - remove middle value -> ["1", "3"]
        result = strukts_linkedlist_remove(list, "2");

        // assert
        EXPECT_TRUE(result);
        EXPECT_EQ(list->size, 2);
        EXPECT_EQ(strcmp(list->first_node->value, one), 0);
        EXPECT_EQ(strcmp(list->last_node->value, three), 0);

        // act - remove last one -> ["1"]
        result = strukts_linkedlist_remove(list, "3");

        // assert
        EXPECT_TRUE(result);
        EXPECT_EQ(list->size, 1);
        EXPECT_EQ(strcmp(list->first_node->value, one), 0);
        EXPECT_EQ(strcmp(list->last_node->value, one), 0);

        // act - remove final element -> []
        result = strukts_linkedlist_remove(list, "1");

        // assert
        EXPECT_TRUE(result);
        EXPECT_EQ(list->size, 0);
        EXPECT_EQ(list->first_node, nullptr);
        EXPECT_EQ(list->last_node, nullptr);

        // act - remove nonexistent element
        result = strukts_linkedlist_remove(list, "10");

        // assert
        EXPECT_FALSE(result);
        EXPECT_EQ(list->size, 0);
        EXPECT_EQ(list->first_node, nullptr);
        EXPECT_EQ(list->last_node, nullptr);

        strukts_linkedlist_free(list);
    }
}  // namespace
