#include "strukts_heap.h"

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

/********************** PUBLIC FUNCTIONS **********************/
StruktsMaxHeap strukts_heap_maxheap_new(int a[], size_t len)
{
    StruktsMaxHeap max_heap = {.array = a, .size = len};

    /*
     * Heapifies the whole array. Notice that there's no need to go beyond
     * the middle of the array (parent_i = len / 2), as heapifying requires
     * fetching children from each parent and as children stay, roughly,
     * at the index (2 * parent_i), these children would be invalid as they
     * would be outside the heap array size boundaries.
     *
     * The loop uses a trick to avoid underflow of a size_t which is always >= 0.
     */
    for (size_t i = 0; i <= len / 2; i++) {
        size_t parent_i = len / 2 - i; /* trick for reverse iterating with size_t */
        strukts_heap_max_heapify(max_heap, parent_i);
    }

    return max_heap;
}

StruktsHeapChildResult strukts_heap_get_child(StruktsMaxHeap heap, size_t parent_i, bool left_child)
{
    StruktsHeapChildResult result = {.valid = false, .value = 0, .position = 0};
    size_t child_position;

    if (left_child)
        child_position = 2 * parent_i + 1;
    else
        child_position = 2 * parent_i + 2;

    result.position = child_position;

    /* index goes beyond the heap array's final index (size - 1): return invalid result */
    if (child_position > heap.size - 1)
        return result;

    result.value = heap.array[child_position];
    result.valid = true;

    return result;
}

int strukts_heap_get_parent(StruktsMaxHeap heap, size_t child_i)
{
    if (child_i % 2 == 0) /* even indexes */
        return heap.array[child_i / 2 - 1];

    return heap.array[child_i / 2];
}

void strukts_heap_max_heapify(StruktsMaxHeap heap, size_t parent_i)
{
    StruktsHeapChildResult left_child = strukts_heap_get_child(heap, parent_i, true);
    StruktsHeapChildResult right_child = strukts_heap_get_child(heap, parent_i, false);
    size_t largest_i = 0;

    /*
     * Compares the parent, heap.array[parent_i], against its children nodes. Here the
     * biggest wins (parent, left or right child). If any of the children is bigger than
     * its parent, then the parent is swapped with its child and heapify is recursively
     * called on the parent's new position (to continue to make sure the max-heap is respected).
     */
    if (left_child.valid && left_child.value > heap.array[parent_i])
        largest_i = left_child.position;
    else
        largest_i = parent_i; /* parent is bigger than left child */

    if (right_child.valid && right_child.value > heap.array[largest_i])
        largest_i = right_child.position; /* right child is the biggest one */

    /* one of the children is bigger than the parent: swap and keep heapifying */
    if (largest_i != parent_i) {
        SWAP(heap.array, parent_i, largest_i);
        strukts_heap_max_heapify(heap, largest_i);
    }
}
