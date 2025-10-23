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