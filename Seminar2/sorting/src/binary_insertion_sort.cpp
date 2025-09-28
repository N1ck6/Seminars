#include "binary_insertion_sort.h"

template <typename T>
void binary_insertion_sort(vector<T>& arr) {
    int n = arr.size();
    if (n <= 1) return;
    int p = 0;
    for (int i = 1; i < n; i++) {
        T tmp = arr[i];
        int p1 = 0;
        int p2 = i;

        while (p1 < p2) {
            int mid = p1 + (p2 - p1) / 2;
            if (arr[mid] <= tmp) {
                p1 = mid + 1;
            }
            else {
                p2 = mid;
            }
        }
        for (int j = i; j > p1; j--) {
            arr[j] = arr[j - 1];
        }
        arr[p1] = tmp;
    }
}

template void binary_insertion_sort<int>(vector<int>& arr);
template void binary_insertion_sort<double>(vector<double>& arr);