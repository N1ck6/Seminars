#include "bubble_sort.h"
#include <iostream>
#include <cassert>

void test_bubble_sort() {
    vector<int> arr = { 64, 34, 25, 12, 22 };
    bubble_sort(arr);

    vector<int> expected = { 12, 22, 25, 34, 64 };
    for (size_t i = 0; i < arr.size(); i++) {
        assert(arr[i] == expected[i]);
    }
    cout << "Test Passed!" << endl;
}

int main() {
    test_bubble_sort();
    return 0;
}