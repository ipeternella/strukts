#include "strukts_sorting.h"

#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

/********************** MACROS **********************/
#define INF INT_MAX

/********************** MERGESORT: PRIVATE FUNCTIONS **********************/
static bool strukts_mergesort_merge(int a[], size_t p, size_t q, size_t r)
{
    /* sizes of the sub arrays to dynamically allocate with ONE extra room to store the sentinel */
    size_t left_len = (q - p + 1) + 1; /* (q - p + 1) gives the exact len of the left subarray */
    size_t right_len = (r - q) + 1;    /* (r - q) gives the exact len of the right subarray */

    /* allocates the new tmp arrays */
    int* left_array = (int*)malloc(left_len * sizeof(int));
    if (left_array == NULL)
        return false;

    int* right_array = (int*)malloc(right_len * sizeof(int));
    if (right_array == NULL) {
        free(left_array);
        return false;
    }

    /* sentinels setting -> max posible values for signed integers */
    left_array[left_len - 1] = INF;
    right_array[right_len - 1] = INF;

    /* fills the sub arrays with elements from the original array */
    for (size_t i = 0; i < left_len - 1; i++)
        left_array[i] = a[p + i];

    for (size_t j = 0; j < right_len - 1; j++)
        right_array[j] = a[q + 1 + j];

    /*
     * pick smaller values from each sub array until are no elements left in order to effectively
     * merge the two already sorted subarrays into a newly sorted array
     */
    size_t i = 0;
    size_t j = 0;

    /* effectively merge-sorting */
    for (size_t k = p; k <= r; k++) {
        /* once a sentinel shows up, all the other elements of the other subarray will be chosen */
        if (left_array[i] <= right_array[j])
            a[k] = left_array[i++];
        else
            a[k] = right_array[j++];
    }

    /* frees allocated memory for tmp subarrays */
    free(left_array);
    free(right_array);

    return true;
}

static inline bool strukts_mergesort_helper(int a[], size_t p, size_t r)
{
    /*
     * Implementation of divide and conquer strategy with mergesort. One point to notice
     * is that the merge operation contains heap allocations that may fail. As such, the
     * internal procedures return booleans that indicates if any allocation has failed.
     * If that's the case, then the sorting function stops and returns false.
     */
    if (p < r) {
        size_t q = (p + r) / 2; /* int division ~ floor operation */

        /* divide the problem: left subarray */
        if (!strukts_mergesort_helper(a, p, q))
            return false;

        /* right subarray */
        if (!strukts_mergesort_helper(a, q + 1, r))
            return false;

        /* .. and conquer: start merging the smaller solved (sorted) problems */
        if (!strukts_mergesort_merge(a, p, q, r))
            return false; /* merge contains allocations that may fail, stop if it happens */
    }

    /* base recursion case: array is already sorted */
    return true;
}

/********************** SORTING PUBLIC FUNCTIONS **********************/
bool strukts_sorting_mergesort(int a[], size_t len)
{
    /* trivial case */
    if (len == 1)
        return true;

    /* calls internal static procedure to ease the use */
    return strukts_mergesort_helper(a, 0, len - 1);
}

bool strukts_sorting_insertionsort(int a[], int len)
{
    /* trivial case */
    if (len == 1)
        return true;

    int j = 0;
    int key = 0;

    for (int i = 1; i < len; i++) {
        key = a[i];

        /* shift right all keys that are bigger than current key */
        for (j = i - 1; j >= 0 && a[j] > key; j--)
            a[j + 1] = a[j];

        /* set key's current position (+1 to remove final j--) */
        a[j + 1] = key;
    }

    return true;
}