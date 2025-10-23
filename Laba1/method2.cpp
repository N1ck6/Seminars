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
