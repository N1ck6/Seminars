#include "selection_sort.h"
#include <algorithm>

template <typename T>
void selection_sort(vector<T>& arr) {
	size_t n = arr.size();
	int min;
	for (size_t i = 0; i < n; i++) {
		min = i;
		for (size_t j = i; j < n; j++) {
			if (arr[j] < arr[min]) min = j;
		}
		swap(arr[i], arr[min]);
	}
}

template void selection_sort<int>(vector<int>& arr);
template void selection_sort<double>(vector<double>& arr);