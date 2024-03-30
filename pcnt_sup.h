#ifndef PCNT_SUP_H
#define PCNT_SUP_H

#include <stdint.h>

#ifdef __GNUC__
    // Define behavior for GNU C and C++ compilers
    #define POPCNT(i) __builtin_popcount(i)
#elif defined(__clang__)
    // Define behavior for Clang
    #define POPCNT(i) __builtin_popcount(i)
#elif defined(__BORLANDC__)
    // Define behavior for Borland C++
    #define POPCNT(i) __popcnt(i)
#elif defined(_MSC_VER)
    // Define behavior for Microsoft Visual C++
    #define POPCNT(i) __popcnt(i)
#else
    // Fallback implementation for other compilers
    static inline int count_set_bits(int i) {
        int count = 0;
        for (; i; i &= i - 1) count++;
        return count;
    }
    #define POPCNT(i) count_set_bits(i)
#endif

// Check if the CPU supports the POPCNT instruction
static inline int cpu_supports_popcnt() {
#if defined(__x86_64__) || defined(__i386__)
    int max_std_func_id = 0;
    int popcnt_supported = 0;

    // Get the maximum standard function ID supported by the CPU
    __cpuid(0, 0, 0, 0, &max_std_func_id);

    // Check if the CPUID feature flags are supported
    if (max_std_func_id >= 1) {
        int feature_flags[4];
        __cpuid(1, feature_flags, feature_flags + 1, feature_flags + 2, feature_flags + 3);

        // Check if the POPCNT instruction is supported
        popcnt_supported = (feature_flags[2] & (1 << 23)) != 0;
    }

    return popcnt_supported;
#else
    // POPCNT is not supported on non-x86 architectures
    return 0;
#endif
}

#endif /* PCNT_SUP_H */
