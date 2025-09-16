#include "selection_sort.h"
#include <algorithm>

void selection_sort(vector<int>& arr) {
	size_t n = arr.size();
	int min;
	for (size_t i = 0; i < n; i++) {
		min = i;
		for (size_t j = i; j < n; j++) {
			if (arr.at(j) < arr.at(min)) min = j;
		}
		swap(arr.at(i), arr.at(min));
	}
}