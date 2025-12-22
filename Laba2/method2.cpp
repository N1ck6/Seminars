#define _CRT_SECURE_NO_WARNINGS
#include "method2.h"
void process_cstring(char str[]) {
    int sum = 0;
    int count = 0;
    char* p = str;

    while (*p != '\0') {
        if (isdigit(*p)) {
            int num = 0;
            while (isdigit(*p)) {
                num = num * 10 + (*p - '0');
                p++;
            }
            sum += num;
            count++;
        }
        else {
            p++;
        }
    }

    char* end = str + strlen(str);
    sprintf(end, "%d&%d", sum, count);
}

char* input_string_calloc() {
    char* str = NULL;
    int chunk_size = 5;
    int size = 0;
    int current_size = chunk_size;
    char c;

    printf("Enter string: ");

    str = (char*)calloc(chunk_size, sizeof(char));
    if (!str) return NULL;

    while ((c = getchar()) != '\n' && c != EOF) {
        if (size >= current_size - 1) {
            current_size += chunk_size;
            char* temp = (char*)realloc(str, current_size * sizeof(char));
            if (!temp) {
                free(str);
                return NULL;
            }
            str = temp;
        }

        str[size] = c;
        size++;
    }

    str[size] = '\0';
    return str;
}