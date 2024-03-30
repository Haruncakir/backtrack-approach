#ifndef SUBSETS_H
#define SUBSETS_H

#include <stddef.h>

/**
 * Generates all possible subsets of a given set of integers.
 *
 * @param nums An array of integers representing the input set.
 * @param numsSize The number of elements in the `nums` array.
 * @param returnSize A pointer to an integer that will store the number of subsets generated.
 * @param returnColumnSizes A pointer to an array that will store the size of each subset.
 *
 * @return An array of arrays, where each inner array represents a subset of the input set.
 */
int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

/**
 * Fallback implementation of the `subsets` function that does not use the `__popcnt` instruction.
 *
 * @param nums An array of integers representing the input set.
 * @param numsSize The number of elements in the `nums` array.
 * @param returnSize A pointer to an integer that will store the number of subsets generated.
 * @param returnColumnSizes A pointer to an array that will store the size of each subset.
 *
 * @return An array of arrays, where each inner array represents a subset of the input set.
 */
int** subsets_fallback(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

#endif // SUBSETS_H
