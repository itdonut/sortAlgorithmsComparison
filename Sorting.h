#ifndef SORTING_H_INCLUDED
#define SORTING_H_INCLUDED

#include <cstdint>
#include <emmintrin.h>
#include <smmintrin.h>

class Sorting {
public:
    template<class T>
    static void bubble(T*, const uint32_t);
    template<class T>
    static void insertion(T*, const uint32_t);
    template<class T>
    static void quick(T*, const int32_t, const int32_t);
    template<class T>
    static void merge(T*, const uint32_t, const uint32_t);
    template<class T>
    static void selection(T*, const uint32_t);

    // SIMD
    static void bubble_SIMD_int32(int32_t*,const uint32_t);
    static void selection_SIMD_int32(int32_t*, const uint32_t);
private:
    template<class T>
    static int32_t partition(T* arr, const int32_t, const int32_t);
    template<class T>
    static void swap(T&, T&);
    template<class T>
    static void merging(T* arr, const uint32_t, const uint32_t, const uint32_t);

    //SIMD
    static inline __m128i emulate_mm_min_epi32(const __m128i, const __m128i);
};

// template member must be implemented in the same file
template<class T>
void Sorting::bubble(T* arr, const uint32_t n) {
    for(uint32_t i = 0; i < n; i++) {
        bool flag = false;
        for(uint32_t j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                flag = true;
                T temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }

        if(!flag) return;
    }
}

template<class T>
void Sorting::insertion(T* arr, const uint32_t n) {
    for (uint32_t i = 1; i < n; ++i) {
        T key = arr[i];
        int32_t j = i - 1;  // can be negative

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }

        arr[j + 1] = key;
    }
}

template<class T>
void Sorting::quick(T* arr, const int32_t low, const int32_t high) {
    if (low < high) {
        int32_t pi = Sorting::partition<T>(arr, low, high); // Partition index

        Sorting::quick<T>(arr, low, pi - 1);  // Sort elements before partition
        Sorting::quick<T>(arr, pi + 1, high); // Sort elements after partition
    }
}

template<class T>
void Sorting::selection(T* arr, const uint32_t n) {
    for (uint32_t i = 0; i < n - 1; i++) {
        uint32_t minIndex = i; // Assume the current element is the minimum

        // Find the index of the minimum element in the remaining array
        for (uint32_t j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum element with the first element
        if (minIndex != i) {
            T temp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = temp;
        }
    }
}

template<class T>
void Sorting::merge(T* arr, const uint32_t left, const uint32_t right) {
    if (left < right) {
        uint32_t mid = left + (right - left) / 2;

        Sorting::merge<T>(arr, left, mid);         // Sort first half
        Sorting::merge<T>(arr, mid + 1, right);    // Sort second half
        Sorting::merging<T>(arr, left, mid, right);      // Merge the two halves
    }
}

template<class T>
int32_t Sorting::partition(T* arr, const int32_t low, const int32_t high) {
    T pivot = arr[high]; // Select the last element as the pivot
    int32_t i = low - 1;       // Index of smaller element (can be negative)

    for (int32_t j = low; j < high; j++) {
        // If current element is smaller than or equal to pivot
        if (arr[j] <= pivot) {
            i++; // Increment index of smaller element
            Sorting::swap<T>(arr[i], arr[j]);
        }
    }
    Sorting::swap<T>(arr[i + 1], arr[high]); // Place pivot in the correct position
    return i + 1;
}

template<class T>
void Sorting::swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template<class T>
void Sorting::merging(T* arr, const uint32_t left, const uint32_t mid, const uint32_t right) {
    uint32_t n1 = mid - left + 1;
    uint32_t n2 = right - mid;

    // Temporary arrays
    int32_t leftArr[n1], rightArr[n2];

    // Copy data to temporary arrays leftArr[] and rightArr[]
    for (uint32_t i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (uint32_t j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    uint32_t i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        } else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArr[], if any
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArr[], if any
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

#endif // SORTING_H_INCLUDED
