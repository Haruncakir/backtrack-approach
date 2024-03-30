#include <stdio.h>
#include <stdlib.h>
#include "subsets.h"
#include "pcnt_sup.h"

int main() {
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int returnSize;
    int* returnColumnSizes;

    int** result;

    // Check if the CPU supports the POPCNT instruction
    if (cpu_supports_popcnt()) {
        printf("CPU supports POPCNT instruction\n");
        result = subsets(nums, numsSize, &returnSize, &returnColumnSizes);
    } else {
        printf("CPU does not support POPCNT instruction\n");
        result = subsets_fallback(nums, numsSize, &returnSize, &returnColumnSizes);
    }

    // Process the subsets...
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d%s", result[i][j], j < returnColumnSizes[i] - 1 ? ", " : "");
        }
        printf("]\n");
    }

    // Free memory
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}
