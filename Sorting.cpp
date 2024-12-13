#include "Sorting.h"

void Sorting::bubble_SIMD_int32(int32_t* arr, const uint32_t n) {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (uint32_t i = 0; i < n - 1; i += 4) {
            if (i + 4 <= n) {
                // Load 4 integers into SSE registers
                __m128i a = _mm_loadu_si128(reinterpret_cast<__m128i*>(&arr[i]));
                __m128i b = _mm_loadu_si128(reinterpret_cast<__m128i*>(&arr[i + 1]));

                // Compare adjacent elements
                __m128i mask = _mm_cmpgt_epi32(a, b);

                // Swap elements if necessary
                __m128i min_vals = Sorting::emulate_mm_min_epi32(a, b);
                __m128i max_vals = Sorting::emulate_mm_min_epi32(a, b);

                // Store swapped results back to array
                _mm_storeu_si128(reinterpret_cast<__m128i*>(&arr[i]), min_vals);
                _mm_storeu_si128(reinterpret_cast<__m128i*>(&arr[i + 1]), max_vals);

                // Check if a swap occurred
                if (_mm_movemask_epi8(mask) != 0) {
                    swapped = true;
                }
            } else {
                // Handle remaining elements sequentially
                if (arr[i] > arr[i + 1]) {
                    Sorting::swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
        }
    }
}

void Sorting::selection_SIMD_int32(int32_t* arr, const uint32_t n) {
    for (uint32_t i = 0; i < n - 1; ++i) {
        // Assume the first unsorted element is the minimum
        uint32_t min_index = i;
        int32_t min_value = arr[i];

        // SIMD block search for minimum in the unsorted part of the array
        for (uint32_t j = i + 1; j + 3 < n; j += 4) {
            // Load 4 integers from arr[j] to arr[j+3]
            __m128i values = _mm_loadu_si128(reinterpret_cast<__m128i*>(&arr[j]));

            // Load the current min_value four times into an SSE register
            __m128i min_vals = _mm_set1_epi32(min_value);

            // Compare to find minimums in the block
            __m128i cmp_mask = _mm_cmpgt_epi32(min_vals, values);

            // Update min_vals with the smaller elements
            min_vals = Sorting::emulate_mm_min_epi32(min_vals, values);

            // Store back potential new min values
            int32_t temp_min[4];
            _mm_storeu_si128(reinterpret_cast<__m128i*>(temp_min), min_vals);

            // Find the minimum value in the temp_min array sequentially
            for (uint32_t k = 0; k < 4; ++k) {
                if (temp_min[k] < min_value) {
                    min_value = temp_min[k];
                    min_index = j + k;
                }
            }
        }

        // Sequential search for the remaining elements (if any) in the block
        for (uint32_t j = (n / 4) * 4; j < n; ++j) {
            if (arr[j] < min_value) {
                min_value = arr[j];
                min_index = j;
            }
        }

        // Swap the found minimum element with the first unsorted element
        if (min_index != i) {
            Sorting::swap<int32_t>(arr[i], arr[min_index]);
        }
    }
}

__m128i Sorting::emulate_mm_min_epi32(const __m128i a, const __m128i b) {
    // Compare 'a' and 'b'. Result is all 1s for elements in 'a' > 'b', else 0.
    __m128i cmp = _mm_cmpgt_epi32(a, b);

    // Blend 'a' and 'b' based on the comparison results:
    // - For elements where a > b (cmp = -1), select 'b'.
    // - For elements where a <= b (cmp = 0), select 'a'.
    return _mm_or_si128(_mm_and_si128(cmp, b), _mm_andnot_si128(cmp, a));
}
