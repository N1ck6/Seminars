#include "bubble_sort.h"
#include <algorithm>

template <typename T>
void bubble_sort(vector<T>& arr) {
	size_t n = arr.size();
	for (size_t i = 0; i < n - 1; i++) {
		for (size_t j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

template void bubble_sort<int>(vector<int>& arr);
template void bubble_sort<double>(vector<double>& arr);