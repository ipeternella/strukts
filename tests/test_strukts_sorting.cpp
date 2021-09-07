#include <stdint.h>
#include <stdio.h>

#include "gtest/gtest.h"
#include "strukts_sorting.h"

namespace
{
    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_WITH_INSERTION_SORT)
    {
        /* arrange */
        int a[] = {5, 2, 4, 6, 1, 3};
        size_t len = 6;

        /* act */
        bool success = strukts_sorting_insertionsort(a, len);

        /* assert */
        int sorted_a[] = {1, 2, 3, 4, 5, 6};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_REPEATED_ELEMENTS_WITH_INSERTION_SORT)
    {
        /* arrange */
        int a[] = {3, 3, 4, 5, 2, 1};
        size_t len = 6;

        /* act */
        bool success = strukts_sorting_insertionsort(a, len);

        /* assert */
        int sorted_a[] = {1, 2, 3, 3, 4, 5};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_TWO_ELEMENTS_WITH_INSERTION_SORT)
    {
        /* arrange */
        int a[] = {7, -1};
        size_t len = 2;

        /* act */
        bool success = strukts_sorting_insertionsort(a, 2);

        /* assert */
        int sorted_a[] = {-1, 7};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_1_ELEMENTS_WITH_INSERTIONSORT)
    {
        /* arrange */
        int a[] = {7};
        size_t len = 1;

        /* act */
        bool success = strukts_sorting_insertionsort(a, len);

        /* assert */
        int sorted_a[] = {7};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_WITH_MERGESORT)
    {
        /* arrange */
        int a[] = {5, 2, 4, 6, 1, 3};
        size_t len = 6;

        /* act */
        bool success = strukts_sorting_mergesort(a, len);

        /* assert */
        int sorted_a[] = {1, 2, 3, 4, 5, 6};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_NEGATIVE_NUMBERS_WITH_MERGESORT)
    {
        /* arrange */
        int a[] = {3, 3, 2, -1};
        size_t len = 4;

        /* act */
        bool success = strukts_sorting_mergesort(a, len);

        /* assert */
        int sorted_a[] = {-1, 2, 3, 3};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_2_ELEMENTS_WITH_MERGESORT)
    {
        /* arrange */
        int a[] = {7, -1};
        size_t len = 2;

        /* act */
        bool success = strukts_sorting_mergesort(a, len);

        /* assert */
        int sorted_a[] = {-1, 7};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_1_ELEMENTS_WITH_MERGESORT)
    {
        /* arrange */
        int a[] = {7};
        size_t len = 1;

        /* act */
        bool success = strukts_sorting_mergesort(a, len);

        /* assert */
        int sorted_a[] = {7};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_WITH_HEAPSORT)
    {
        /* arrange */
        int a[] = {5, 2, 4, 6, 1, 3};
        size_t len = 6;

        /* act */
        bool success = strukts_sorting_heapsort(a, len);

        /* assert */
        int sorted_a[] = {1, 2, 3, 4, 5, 6};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_FEWER_ELEMENTS_WITH_HEAPSORT)
    {
        /* arrange */
        int a[] = {5, 2, 2, 6, 1};
        size_t len = 5;

        /* act */
        bool success = strukts_sorting_heapsort(a, len);

        /* assert */
        int sorted_a[] = {1, 2, 2, 5, 6};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_TWO_ELEMENTS_WITH_HEAPSORT)
    {
        /* arrange */
        int a[] = {5, 2};
        size_t len = 2;

        /* act */
        bool success = strukts_sorting_heapsort(a, len);

        /* assert */
        int sorted_a[] = {2, 5};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }

    TEST(STRUKTS_SORTING_SUITE, SHOULD_SORT_ARRAY_ONE_ELEMENT_WITH_HEAPSORT)
    {
        /* arrange */
        int a[] = {7};
        size_t len = 1;

        /* act */
        bool success = strukts_sorting_heapsort(a, len);

        /* assert */
        int sorted_a[] = {7};

        EXPECT_TRUE(0 == memcmp(a, sorted_a, len * sizeof(int)));
        EXPECT_TRUE(success);
    }
}  // namespace
