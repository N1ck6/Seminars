#include "exchange_sort.h"

template <typename T>
void insertion_sort(vector<T>& arr) {
    size_t n = arr.size();
    for (size_t i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

template void insertion_sort<int>(vector<int>& arr);
template void insertion_sort<double>(vector<double>& arr);