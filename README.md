# Subset Generation in C

This C program generates all possible subsets of a given set of integers. It uses bitwise operations to efficiently generate subsets and dynamically allocates memory to store the subsets.

## How it Works

1. The `subsets` function takes three arguments:
	* `nums`: An array of integers representing the input set.
	* `numsSize`: The number of elements in the `nums` array.
	* `returnSize`: A pointer to an integer that will store the number of subsets generated.
	* `returnColumnSizes`: A pointer to an array that will store the size of each subset.
2. The function calculates the total number of subsets (`2^numsSize`) and dynamically allocates memory for two arrays:
	* `rv`: An array of pointers, where each pointer will point to a subset.
	* `returnColumnSizes`: An array that will store the size of each subset.
3. For each subset:
	* It calculates the number of elements in the subset by counting the number of set bits in the binary representation of the subset index (`i`). This is done using the `POPCNT` macro, which is defined using the `__builtin_popcount` function for compilers that support it, and a fallback implementation for other compilers.
	* It dynamically allocates memory for the subset based on its size.
	* It iterates over each element in the input set and includes the element in the subset if its corresponding bit in `i` is set.
4. Finally, the function returns the array `rv`, which contains all the subsets, and updates the `returnSize` and `returnColumnSizes` variables.

## Usage

1. Include the `subsets.h` header file in your C program.
2. Call the `subsets` function with the input set and retrieve the generated subsets.
3. Iterate over the subsets and process them as needed.
4. Free the memory allocated for the subsets and the `returnColumnSizes` array using the `free` function.

## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include "subsets.h"

int main() {
    // Example usage
    int nums[] = {1, 2, 3};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int returnSize;
    int* returnColumnSizes;

    int** result = subsets(nums, numsSize, &returnSize, &returnColumnSizes);

    // Process the subsets...
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d%s", result[i][j], j < returnColumnSizes[i] - 1 ? ", " : "");
        }
        printf("]\n");
    }

    // Free the memory allocated for the subsets and the returnColumnSizes array
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}
```

## Dependencies

The program uses the `__builtin_popcount` function, which is available in GCC and Clang compilers. For other compilers, a fallback implementation is provided using a loop to count the set bits. The `pcnt_sup.h` header file is used to determine whether the `__builtin_popcount` function is available at compile time.

## Contributing

Contributions are welcome! Please open an issue or a pull request if you have any suggestions or improvements.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

