/**
 * @file strukts_heap.h
 *
 * @brief Module that contains heap implementations.
 *
 * Binary heaps are ARRAY objects that represent binary trees and, as such, can provide
 * efficient operations. There are two types of binary heaps:
 *
 * - max-heap: the root contains the largest element:  a[parent(i)] >= a[i]
 * - min-heap: the root contains the smallest element: a[parent(i)] <= a[i]
 */

#ifndef STRUKTS_HEAP_H
#define STRUKTS_HEAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

/********************** MACROS **********************/
#define SWAP(arr, i, j) \
    int old = arr[i];   \
    arr[i] = arr[j];    \
    arr[j] = old

/**
 * Represents a max-heap data structure in which an array can be viewed as a binary tree.
 */
typedef struct _StruktsMaxHeap StruktsMaxHeap;

struct _StruktsMaxHeap {
    int* array; /* pointer to a heap array */
    size_t size;
};

/**
 * Represents child metadata of some parent node. If the result is within
 * the heap array's bondaries, valid = true. Otherwise, valid = false.
 */
typedef struct _StruktsHeapChildResult StruktsHeapChildResult;

struct _StruktsHeapChildResult {
    int value;
    size_t position;
    bool valid;
};

/**
 * Builds a new binary heap (max-heap) from a given array in-place. This method mutates
 * the array contents to organize it according to the rules of a max-heap.
 *
 * @param a is the array in which the heap will be built upon;
 * @param len is the size of the array;
 *
 * @return a struct of a max-heap.
 */
StruktsMaxHeap strukts_heap_maxheap_new(int a[], size_t len);

/**
 * Gets the left (or right) child of a given parent node which is in index i. If the given parent
 * node would have children beyond the array's bondaries, the StruktsHeapChildResult will contain
 * the property 'valid' set to false. Otherwise, 'valid' is set to true and the child is in the
 * heap. Roughly works like a 'maybe' monad.
 *
 * @param heap is a max-heap struct.
 * @param parent_i is the index of the parent node whose child will be searched for.
 * @param left_child boolean which indicates to get the left child; if false, returns the right
 * child.
 *
 * @return StruktsHeapChildResult struct which will contain metadata of the child such as its value,
 * its position and whether this is a valid result or not (within the bondaries of the array of the
 * heap). If valid is set to false, both the value and position should not be used.
 */
StruktsHeapChildResult strukts_heap_get_child(StruktsMaxHeap heap, size_t parent_i,
                                              bool left_child);

/**
 * Gets the parent's value of a given child node that can be found in index i.
 *
 * @param heap is a max-heap struct.
 * @param child_i is the index of the child node whose parent will be searched for.
 *
 * @return the value of the parent node.
 */
int strukts_heap_get_parent(StruktsMaxHeap heap, size_t child_i);

/**
 * Heapifies (mutates) the heap's array in order to guarantee the max-heap structure in which
 * any parent is always bigger/equal than its children. Hence:
 *
 * - heap->array[parent(i)] >= heap->array[i]
 *
 * Heapifying can start from any index i. If i = 0 (root), then it heapifies the whole array
 * (tree).
 *
 * @param heap is a max-heap struct.
 * @param parent_i is the index of the desired 'parent node' to begin heapifying from.
 */
void strukts_heap_max_heapify(StruktsMaxHeap heap, size_t parent_i);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_HEAP_H */