#include "exchange_sort.h"
#include <algorithm>

template <typename T>
void exchange_sort(vector<T>& arr) {
	size_t n = arr.size();
	for (size_t i = 0; i < n; i++) {
		for (size_t j = i; j < n; j++) {
			if (arr[i] > arr[j]) swap(arr[j], arr[i]);
		}
	}
}

template void exchange_sort<int>(vector<int>& arr);
template void exchange_sort<double>(vector<double>& arr);