#include "insertion_sort.h"
#include <iostream>
#include <cassert>

void test_insertion_sort() {
    vector<int> arr = { 64, 34, 25, 12, 22 };
    insertion_sort(arr);

    vector<int> expected = { 12, 22, 25, 34, 64 };
    for (size_t i = 0; i < arr.size(); i++) {
        assert(arr[i] == expected[i]);
    }
    cout << "Test Passed!" << endl;
}

int main() {
    test_insertion_sort();
    return 0;
}