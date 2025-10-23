#define CATCH_CONFIG_MAIN
#define _CRT_SECURE_NO_WARNINGS
#include <catch.hpp>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "method1.h"
#include "method2.h"
#include "method3.h"
using namespace std;

string read_file() {
    char res[256];
    FILE* in = fopen("Laba1/output.txt", "r");
    if (in && fgets(res, 256, in) != NULL) {
        fclose(in);
    }
    return res;
}

void write_file(const char str[]) {
    FILE* out = fopen("Laba1/input.txt", "w");
    if (!out) return;
    fputs(str, out);
    fclose(out);
}

TEST_CASE("Array String Processing: Empty string", "[array_string]") {
    char str[256] = "";
    process_string(str);
    REQUIRE(strcmp(str, "0&0") == 0);
}

TEST_CASE("Array String Processing: String without digits", "[array_string]") {
    char str[256] = "Hello world!";
    process_string(str);
    REQUIRE(strcmp(str, "Hello world!0&0") == 0);
}

TEST_CASE("Array String Processing: String with one digit", "[array_string]") {
    char str[256] = "A1B";
    process_string(str);
    REQUIRE(strcmp(str, "A1B1&1") == 0);
}

TEST_CASE("Array String Processing: String with multiple digit groups", "[array_string]") {
    char str[256] = "abc123xyz45";
    process_string(str);
    REQUIRE(strcmp(str, "abc123xyz45168&2") == 0);
}

TEST_CASE("Array String Processing: String with digits at beginning, middle and end", "[array_string]") {
    char str[256] = "123abc456def789";
    process_string(str);
    REQUIRE(strcmp(str, "123abc456def7891368&3") == 0);
}

TEST_CASE("Array String Processing: String with negative numbers", "[array_string]") {
    char str[256] = "Value: -123, another value: -45";
    process_string(str);
    REQUIRE(strcmp(str, "Value: -123, another value: -45168&2") == 0);
}



TEST_CASE("C String Processing: Empty string", "[c_string]") {
    char str[256] = "";
    process_cstring(str);
    REQUIRE(strcmp(str, "0&0") == 0);
}

TEST_CASE("C String Processing: String without digits", "[c_string]") {
    char str[256] = "Hello world!";
    process_cstring(str);
    REQUIRE(strcmp(str, "Hello world!0&0") == 0);
}

TEST_CASE("C String Processing: String with one digit", "[c_string]") {
    char str[256] = "A1B";
    process_cstring(str);
    REQUIRE(strcmp(str, "A1B1&1") == 0);
}

TEST_CASE("C String Processing: String with multiple digit groups", "[c_string]") {
    char str[256] = "abc123xyz45";
    process_cstring(str);
    REQUIRE(strcmp(str, "abc123xyz45168&2") == 0);
}

TEST_CASE("C String Processing: String with digits at beginning, middle and end", "[c_string]") {
    char str[256] = "123abc456def789";
    process_cstring(str);
    REQUIRE(strcmp(str, "123abc456def7891368&3") == 0);
}

TEST_CASE("C String Processing: String with negative numbers", "[c_string]") {
    char str[256] = "Value: -123, another value: -45";
    process_cstring(str);
    REQUIRE(strcmp(str, "Value: -123, another value: -45168&2") == 0);
}



TEST_CASE("File String Processing: Empty file", "[file_string]") {
    write_file("");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "0&0");
}

TEST_CASE("File String Processing: File without digits", "[file_string]") {
    write_file("Hello world!");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "Hello world!0&0");
}

TEST_CASE("File String Processing: File with one digit group", "[file_string]") {
    write_file("abc123xyz");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "abc123xyz123&1");
}

TEST_CASE("File String Processing: File with multiple digit groups", "[file_string]") {
    write_file("abc123xyz45");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "abc123xyz45168&2");
}

TEST_CASE("File String Processing: File with digits at beginning, middle and end", "[file_string]") {
    write_file("123abc456def789");
    process_file_string();
    string result = read_file();
    REQUIRE(result == "123abc456def7891368&3");
}