#include "optimized_bubble_sort.h"
#include <algorithm>

template <typename T>
void optimized_bubble_sort(vector<T>& arr) {
	size_t n = arr.size();
	if (n <= 1) return;
	bool f;
	int p = n - 1;
	int p1;
	for (size_t i = 0; i < n - 1; i++) {
		f = false;
		p1 = 0;
		for (size_t j = 0; j < p; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				f = true;
				p1 = j;
			}
		}
		p = p1;
		if (!f) break;
	}
}

template void optimized_bubble_sort<int>(vector<int>& arr);
template void optimized_bubble_sort<double>(vector<double>& arr);