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

        strukts_linkedlist_free(list);
    }

    TEST(STRUKTS_LINKEDLISTS_SUITE, SHOULD_FIND_ELEMENT_IN_THE_LINKED_LIST) {
        // arrange - create list ["1", "2", "3"]
        StruktsLinkedList *list = strukts_linkedlist_new();

        const char *one = "1";
        const char *two = "2";
        const char *three = "3";
        const char *not_in_list = "7";

        strukts_linkedlist_append(list, one);
        strukts_linkedlist_append(list, two);
        strukts_linkedlist_append(list, three);

        // act
        bool has_value = strukts_linkedlist_contains(list, two);

        // assert
        EXPECT_TRUE(has_value);

        // act
        has_value = strukts_linkedlist_contains(list, not_in_list);  // not in the list

        // assert
        EXPECT_FALSE(has_value);

        strukts_linkedlist_free(list);  // frees testing memory
    }
}  // namespace
