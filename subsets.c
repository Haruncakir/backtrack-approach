#include <stdlib.h>
#include "subsets.h"
#include "pcnt_sup.h"

/**
 * Counts the number of set bits in an integer using Brian Kernighan's Algorithm.
 *
 * @param n An integer for which the number of set bits is to be counted.
 *
 * @return The number of set bits in the input integer.
 */
static int count_set_bits(int n) {
    int count = 0;
    while (n) {
        n &= (n - 1);
        count++;
    }
    return count;
}

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 1 << numsSize; // Power set of S always has 2^|S| elements

    // Allocate memory for the array of arrays and the returnColumnSizes array
    int** rv = malloc(sizeof(*rv) * (*returnSize));
    *returnColumnSizes = malloc(sizeof(**returnColumnSizes) * (*returnSize));

    for (int i = 0; i < *returnSize; ++i) {
        // Calculate the number of set bits in the subset index
        int num_set_bits = __builtin_popcount(i);

        // Allocate memory for the current subset
        rv[i] = malloc(sizeof(*(rv[i])) * num_set_bits);
        (*returnColumnSizes)[i] = num_set_bits;

        // Iterate over each element in the input set
        int idx = 0;
        for (int j = 0; j < numsSize; ++j) {
            // If the jth bit in the subset index is set, include the jth element in the subset
            if (i & (1 << j)) {
                rv[i][idx++] = nums[j];
            }
        }
    }

    return rv;
}

int** subsets_fallback(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 1 << numsSize; // Power set of S always has 2^|S| elements

    // Allocate memory for the array of arrays and the returnColumnSizes array
    int** rv = malloc(sizeof(*rv) * (*returnSize));
    *returnColumnSizes = malloc(sizeof(**returnColumnSizes) * (*returnSize));

    for (int i = 0; i < *returnSize; ++i) {
        // Calculate the number of set bits in the subset index
        int num_set_bits = count_set_bits(i);

        // Allocate memory for the current subset
        rv[i] = malloc(sizeof(*(rv[i])) * num_set_bits);
        (*returnColumnSizes)[i] = num_set_bits;

        // Iterate over each element in the input set
        int idx = 0;
        for (int j = 0; j < numsSize; ++j) {
            // If the jth bit in the subset index is set, include the jth element in the subset
            if (i & (1 << j)) {
                rv[i][idx++] = nums[j];
            }
        }
    }

    return rv;
}
