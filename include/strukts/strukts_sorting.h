/**
 * @file strukts_sorting.h
 *
 * @brief Module that contains sorting implementations.
 */

#ifndef STRUKTS_SORTING_H
#define STRUKTS_SORTING_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>

/**
 * Performs an in-place sorting of an int array a using insertion sort. As insertion
 * sort runs in O(n^2), the len param is an int and not a size_t to avoid some complications
 * due to size_t underflows.
 *
 * @param a is an array of integers which will be sorted in place.
 * @param len is the length of array.
 *
 * @return true if the sorting was successful; false, otherwise.
 */
bool strukts_sorting_insertionsort(int a[], int len);

/**
 * Performs an in-place sorting of an int array using mergesort (algorithm based on the divide and
 * conquer strategy).
 *
 * @param a is an array of integers which will be sorted in place.
 * @param len is the length of array.
 *
 * @return true if the sorting was successful; false, otherwise.
 */
bool strukts_sorting_mergesort(int a[], size_t len);

/**
 * Performs an in-place sorting of an int array using heapsort.
 *
 * @param a is an array of integers which will be sorted in place.
 * @param len is the length of array.
 *
 * @return true if the sorting was successful; false, otherwise.
 */
bool strukts_sorting_heapsort(int a[], size_t len);

#ifdef __cplusplus
}
#endif
#endif /* STRUKTS_SORTING_H */