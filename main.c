#include <stdio.h>
#include <stdlib.h>

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes);

int main() {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int returnSize;
    int* returnColumnSizes;

    int** result = subsets(nums, numsSize, &returnSize, &returnColumnSizes);

    printf("Number of subsets: %d\n", returnSize);
    printf("Subsets:\n");
    for (int i = 0; i < returnSize; ++i) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; ++j) {
            printf("%d", result[i][j]);
            if (j < returnColumnSizes[i] - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }

    // Free memory
    for (int i = 0; i < returnSize; ++i) {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}

/*

  Alternative function for __builtin_popcount :
  This function counts the number of set bits (bits with value 1) in an integer using
  Brian Kernighan's Algorithm. It repeatedly clears the least significant set bit
  of the input integer until the entire integer becomes zero, counting the number
  of times it performs this operation. This approach is efficient because it only
  processes the bits that are set in the input integer.

  Example:
    Input:  23 (0b00010111)
    Output: 4 (four bits are set: 1, 4, 5, 8)

  Parameters:
    n: An integer for which the number of set bits is to be counted.

  Returns:
    The number of set bits in the input integer.

  int count_set_bits(int n) {
    int count = 0;
    while (n) {
      n &= (n - 1);
      count++;
    }
    return count;
  }

*/


int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
  *returnSize = 1 << numsSize; // Power set of S always has 2^|S| elements

  /* Allocating memory dynamically */
  int** rv = malloc(sizeof(*rv) * (*returnSize));  // Returned array of arrays
  *returnColumnSizes = malloc(sizeof(**returnColumnSizes) * *returnSize);  // columnSizes output

  for (int i = 0; i < *returnSize; ++i) {
    /* popcount is an x86 instruction which returns the number of 1 bits in a register */
    /* GCC compiler supports a similar instruction, regardless of platform */
    (*returnColumnSizes)[i] = __builtin_popcount(i);              // Let client know length of array

    rv[i] = malloc(sizeof(*(rv[i])) * (*returnColumnSizes)[i]);   // Allocate array
    int rvi_idx = 0;                                              // Index into newly allocated rv[i] array

    /* Each of the first numsSize bits of `i` is associated with an integer in nums */
    for (int idx = 0; idx < numsSize; ++idx) {
      if ((1 << idx) & i) {
        /* If the idx'th bit of `i` is 1, then we add the idx'th num to rv[i] */
        rv[i][rvi_idx++] = nums[idx];
      }
    }
  }
  return rv;
}

/*
  This function generates all possible subsets of a given set of integers using
  a classic recursive backtracking approach. It recursively explores all possible
  combinations of including or excluding each element in the input set to generate
  all subsets.

  Parameters:
    nums: An array of integers representing the input set.
    numsSize: The number of elements in the input set.
    returnSize: A pointer to an integer that will store the number of subsets generated.
    returnColumnSizes: A pointer to an array that will store the size of each subset.

  Returns:
    An array of arrays, where each inner array represents a subset of the input set.
    The function also updates returnSize with the total number of subsets and
    returnColumnSizes with the size of each subset.

  Example:
    Input: nums = [1, 2, 3]
    Output: [[], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]]

void backtrack(int* nums, int numsSize, int start, int* subset, int subsetSize, int** result, int* resultSize, int** resultColumnSizes) {
  result[*resultSize] = (int*) malloc(sizeof(int) * subsetSize);
  for (int i = 0; i < subsetSize; i++) {
    result[*resultSize][i] = subset[i];
  }
  (*resultColumnSizes)[*resultSize] = subsetSize;
  (*resultSize)++;

  for(int i = start; i < numsSize; ++i) {
    subset[subsetSize] = nums[i];
    backtrack(nums, numsSize, i + 1, subset, subsetSize + 1, result, resultSize, resultColumnSizes);
  }
}

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int totalSubsets = 1 << numsSize; // pow(2, numsSize);

    int** result = (int**)malloc(totalSubsets * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalSubsets * sizeof(int));
    *returnSize = 0;

    // Temporary array to store each subset
    int* subset = (int*)malloc(numsSize * sizeof(int));

    backtrack(nums, numsSize, 0, subset, 0, result, returnSize, returnColumnSizes);

    free(subset);
    return result;
}

*/
