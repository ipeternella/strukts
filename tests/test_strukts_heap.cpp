#include "gtest/gtest.h"
#include "strukts_heap.h"

namespace
{
    TEST(STRUKTS_HEAP_SUITE, SHOULD_BUILD_HEAP_FROM_ARRAY)
    {
        /* arrange */
        int a[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
        size_t len = 10;

        /* act */
        StruktsMaxHeap heap = strukts_heap_maxheap_new(a, len);

        /* assert */
        int expected[] = {16, 14, 10, 8, 7, 9, 3, 2, 4, 1};

        EXPECT_TRUE(0 == memcmp(heap.array, expected, len * sizeof(int)));
    }
}  // namespace
