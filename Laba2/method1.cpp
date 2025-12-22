#define _CRT_SECURE_NO_WARNINGS
#include "method1.h"
void process_string(char str[]) {
    int sum = 0;
    int count = 0;
    int i = 0;

    while (str[i] != '\0') {
        if (isdigit(str[i])) {
            int num = 0;
            while (isdigit(str[i])) {
                num = num * 10 + (str[i] - '0');
                i++;
            }
            sum += num;
            count++;
        }
        else {
            i++;
        }
    }

    sprintf(str + strlen(str), "%d&%d", sum, count);
}

char* input_string_malloc() {
    char* str = NULL;
    int size = 0;
    char c;

    printf("Enter string: ");
    str = (char*)malloc(1 * sizeof(char));
    if (!str) return NULL;

    while ((c = getchar()) != '\n' && c != EOF) {
        char* temp = (char*)malloc((size + 1) * sizeof(char));
        if (!temp) {
            free(str);
            return NULL;
        }

        for (int i = 0; i < size; i++) {
            temp[i] = str[i];
        }
        temp[size] = c;
        size++;
        free(str);
        str = temp;
    }
    char* temp = (char*)malloc((size + 1) * sizeof(char));
    if (!temp) {
        free(str);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        temp[i] = str[i];
    }
    temp[size] = '\0';
    free(str);
    return temp;
}