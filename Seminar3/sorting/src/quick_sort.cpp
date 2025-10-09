#include "shaker_sort.h"
#include <algorithm>

template <typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}


template <typename T>
void quick_sort(vector<T>& arr, int low, int high) {
    if (high <= 0) return;

    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quick_sort(arr, low, pivotIndex - 1);
        quick_sort(arr, pivotIndex + 1, high);
    }
}

template <typename T>
void quick_sort(vector<T>& arr) {
    quick_sort(arr, 0, arr.size() - 1);
}

template void quick_sort<int>(vector<int>& arr);
template void quick_sort<double>(vector<double>& arr);