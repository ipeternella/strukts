#include <string.h>

#include "gtest/gtest.h"
#include "strukts_linkedlist.h"

namespace {
    TEST(STRUKTS_LINKEDLISTS_SUITE, SHOULD_CREATE_AND_REMOVE_ITEMS_FROM_DOUBLY_LINKED_LIST) {
        // arrange & act
        StruktsLinkedList* list = strukts_linkedlist_new();

        // assert
        EXPECT_EQ(list->size, 0);

        // act - add elements to the beginning
        strukts_linkedlist_prependkv(list, "10");
        strukts_linkedlist_prependkv(list, "20");
        strukts_linkedlist_prependkv(list, "30");

        // assert - ["30", "20", "10"]
        EXPECT_EQ(list->size, 3);
        EXPECT_EQ(strcmp(list->first_node->key, "30"), 0);
        EXPECT_EQ(strcmp(list->first_node->value, "30"), 0);
        EXPECT_EQ(strcmp(list->last_node->key, "10"), 0);
        EXPECT_EQ(strcmp(list->last_node->value, "10"), 0);

        // act - add elements to the end
        strukts_linkedlist_appendkv(list, "40");
        strukts_linkedlist_appendkv(list, "50");

        // assert - ["30", "20", "10", "40", "50"]
        EXPECT_EQ(list->size, 5);
        EXPECT_EQ(strcmp(list->first_node->key, "30"), 0);
        EXPECT_EQ(strcmp(list->last_node->key, "50"), 0);

        // act - remove first element
        strukts_linkedlist_remove_first(list);

        // assert - ["20", "10", "40", "50"]
        EXPECT_EQ(list->size, 4);
        EXPECT_EQ(strcmp(list->first_node->key, "20"), 0);
        EXPECT_EQ(strcmp(list->last_node->key, "50"), 0);

        // act - remove last element
        strukts_linkedlist_remove_last(list);

        // assert - ["20", "10", "40"]
        EXPECT_EQ(list->size, 3);
        EXPECT_EQ(strcmp(list->first_node->key, "20"), 0);
        EXPECT_EQ(strcmp(list->last_node->key, "40"), 0);

        strukts_linkedlist_free(list);
    }

    TEST(STRUKTS_LINKEDLISTS_SUITE, SHOULD_FIND_ELEMENT_IN_THE_LINKED_LIST) {
        // arrange - create list ["1", "2", "3"]
        StruktsLinkedList* list = strukts_linkedlist_new();
        StruktsLinearSearchResult search_result;

        strukts_linkedlist_appendkv(list, "1");
        strukts_linkedlist_appendkv(list, "2");
        strukts_linkedlist_appendkv(list, "3");

        // act - search in ["1", "2", "3"]
        search_result = strukts_linkedlist_find(list, "1");

        // assert
        EXPECT_TRUE(search_result.found);
        EXPECT_EQ(search_result.position, 0);
        EXPECT_EQ(strcmp(search_result.node->key, "1"), 0);
        EXPECT_EQ(strcmp(search_result.node->value, "1"), 0);

        // act
        search_result = strukts_linkedlist_find(list, "2");

        // assert
        EXPECT_TRUE(search_result.found);
        EXPECT_EQ(search_result.position, 1);

        // act
        search_result = strukts_linkedlist_find(list, "3");

        // assert
        EXPECT_TRUE(search_result.found);
        EXPECT_EQ(search_result.position, 2);

        // act
        search_result = strukts_linkedlist_find(list, "7");  // not in the list

        // assert
        EXPECT_FALSE(search_result.found);  // not found
        EXPECT_EQ(search_result.position, 0);
        EXPECT_EQ(search_result.node, nullptr);

        // act - remove last element and search for it - ["1", "2"]
        strukts_linkedlist_remove_last(list);
        search_result = strukts_linkedlist_find(list, "3");

        // assert
        EXPECT_FALSE(search_result.found);  // not found
        EXPECT_EQ(search_result.position, 0);
        EXPECT_EQ(search_result.node, nullptr);

        strukts_linkedlist_free(list);  // frees testing memory
    }

    TEST(STRUKTS_LINKEDLISTS_SUITE, SHOULD_REMOVE_ELEMENTS_FROM_LINKEDLIST) {
        // arrange - create list ["1", "2", "3"]
        StruktsLinkedList* list = strukts_linkedlist_new();
        bool result;

        strukts_linkedlist_appendkv(list, "1");
        strukts_linkedlist_appendkv(list, "2");
        strukts_linkedlist_appendkv(list, "3");

        // act - remove middle value -> ["1", "3"]
        result = strukts_linkedlist_remove(list, "2");

        // assert
        EXPECT_TRUE(result);
        EXPECT_EQ(list->size, 2);
        EXPECT_EQ(strcmp(list->first_node->value, "1"), 0);
        EXPECT_EQ(strcmp(list->last_node->value, "3"), 0);

        // act - remove last one -> ["1"]
        result = strukts_linkedlist_remove(list, "3");

        // assert
        EXPECT_TRUE(result);
        EXPECT_EQ(list->size, 1);
        EXPECT_EQ(strcmp(list->first_node->value, "1"), 0);
        EXPECT_EQ(strcmp(list->last_node->value, "1"), 0);

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
