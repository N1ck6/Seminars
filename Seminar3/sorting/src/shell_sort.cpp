#include "shell_sort.h"

template <typename T>
void shell_sort(vector<T>& arr) {
    int n = arr.size();
    if (n <= 1) return;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            T tmp = arr[i];

            int j;
            for (j = i; j >= gap && arr[j - gap] > tmp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = tmp;
        }
    }
}

template void shell_sort<int>(vector<int>& arr);
template void shell_sort<double>(vector<double>& arr);