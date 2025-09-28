#include "shaker_sort.h"
#include <algorithm>

template <typename T>
void shaker_sort(vector<T>& arr) {
	size_t n = arr.size();
	if (n <= 1) return;
	int p1 = 0;
	int p2 = n - 1;
	bool f = true;
	while (p1 < p2 && f) {
		f = false;
		for (int j = p1; j < p2; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				f = true;
			}
		}
		p2--;
		for (int j = p2; j > p1; j--) {
			if (arr[j] < arr[j - 1]) {
				swap(arr[j], arr[j - 1]);
				f = true;
			}
		}
		p1++;
	}
}

template void shaker_sort<int>(vector<int>& arr);
template void shaker_sort<double>(vector<double>& arr);