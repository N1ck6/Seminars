#define CATCH_CONFIG_MAIN
#include "catch2/catch_amalgamated.hpp"
#include "shell_sort.h"
#include <vector>
#include <algorithm>

TEST_CASE("Sort - Basic", "[sort]") {
    SECTION("My Array") {
        vector<int> arr = { 1, 8, 19, 3, 12, 16, 9, 5 };
        vector<int> expected = { 1, 3, 5, 8, 9, 12, 16, 19 };

        shell_sort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Integer sorting") {
        vector<int> arr = { 5, 2, 8, 1, 3 };
        vector<int> expected = { 1, 2, 3, 5, 8 };

        shell_sort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Double precision sorting") {
        vector<double> arr = { 5.5, 2.2, 8.8, 1.1, 3.3 };
        vector<double> expected = { 1.1, 2.2, 3.3, 5.5, 8.8 };

        shell_sort(arr);

        REQUIRE(arr == expected);
    }
}

TEST_CASE("Sort - Unique", "[sort][unique-cases]") {
    SECTION("Sorted array") {
        vector<int> arr = { 1, 2, 3, 4, 5 };
        vector<int> expected = { 1, 2, 3, 4, 5 };

        shell_sort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Reverse order array") {
        vector<int> arr = { 5, 4, 3, 2, 1 };
        vector<int> expected = { 1, 2, 3, 4, 5 };

        shell_sort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Single element array") {
        vector<int> arr = { 42 };
        vector<int> expected = { 42 };

        shell_sort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Empty array") {
        vector<int> arr;
        vector<int> expected;

        shell_sort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Negative numbers array") {
        vector<int> arr = { -5, -1, -3, 0, 2 };
        vector<int> expected = { -5, -3, -1, 0, 2 };

        shell_sort(arr);

        REQUIRE(arr == expected);
    }
}

TEST_CASE("Sort - Performance", "[sort][performance]") {
    SECTION("Array with duplicates") {
        vector<int> arr = { 3, 1, 2, 3, 1, 2 };
        vector<int> expected = { 1, 1, 2, 2, 3, 3 };

        shell_sort(arr);

        REQUIRE(arr == expected);
    }

    SECTION("Large array") {
        vector<int> arr;
        for (int i = 100; i > 0; --i) {
            arr.push_back(i);
        }

        vector<int> expected;
        for (int i = 1; i <= 100; ++i) {
            expected.push_back(i);
        }

        shell_sort(arr);

        REQUIRE(arr == expected);
    }
}