#include "optimized_bubble_sort.h"
#include <cassert>
#include <iostream>

void test_optimized_bubble_sort() {
	vector<int> arr = { 64, 34, 25, 12, 22 };
	optimized_bubble_sort(arr);

	vector<int> expected = { 12, 22, 25, 34, 64 };
	for (size_t i = 0; i < arr.size(); i++) {
		assert(arr.at(i) == expected.at(i));
	}

	cout << "Test Passed!" << endl;
}

int main() {
	test_optimized_bubble_sort();
	return 0;
}