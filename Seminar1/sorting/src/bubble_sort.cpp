#include "bubble_sort.h"
#include <algorithm>

void bubble_sort(vector<int>& arr) {
	size_t n = arr.size();
	for (size_t i = 0; i < n - 1; i++) {
		for (size_t j = 0; j < n - i - 1; j++) {
			if (arr.at(j) > arr.at(j + 1)) {
				swap(arr.at(j), arr.at(j + 1));
			}
		}
	}
}