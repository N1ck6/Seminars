#include "exchange_sort.h"
#include <algorithm>

void exchange_sort(vector<int>& arr) {
	size_t n = arr.size();
	for (size_t i = 0; i < n; i++) {
		for (size_t j = i; j < n; j++) {
			if (arr.at(i) > arr.at(j)) swap(arr.at(j), arr.at(i));;
		}
	}
}