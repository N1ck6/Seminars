#include <stdio.h>
#include <iostream>
using namespace std;

void process_string(char str[], int max_size) {
    int len = max_size;
    for (int i = 0; i < max_size; i++) {
        if (str[i] == '\0') {
            len = i;
            break;
        }
    }

    long long total_sum = 0;
    int count = 0;

    long long num = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            num = num * 10 + (str[i] - '0');
        }
        else {
            if (num > 0) {
                total_sum += num;
                count++;
                num = 0;
            }
        }
    }

    if (num > 0) {
        total_sum += num;
        count++;
    }

    int required_length = 0;

    if (total_sum == 0) {
        str[len++] = '0';
    }
    else {
        int pos = len - 1;
        long long temp = total_sum;
        while (temp > 0) {
            pos++;
            temp /= 10;
            len++;
        }

        temp = total_sum;
        while (temp > 0) {
            str[pos--] = (temp % 10) + '0';
            temp /= 10;
        }
    }

    str[len++] = '&';

    if (count == 0) {
        str[len++] = '0';
    }
    else {
        int temp = count;
        int pos = len - 1;
        while (temp > 0) {
            pos++;
            temp /= 10;
            len++;
        }

        temp = count;
        while (temp > 0) {
            str[pos--] = (temp % 10) + '0';
            temp /= 10;
        }
    }

    str[len] = '\0';
}

int main() {
    const int MAX_SIZE = 256;
    char str[MAX_SIZE];
    setlocale(LC_ALL, "Rus");

    printf("¬ведите строку: ");
    fgets(str, MAX_SIZE, stdin);

    int len = 0;
    while (str[len] != '\0' && str[len] != '\n') len++;
    if (str[len] == '\n') str[len] = '\0';
    
    process_string(str, MAX_SIZE);

    printf(str);
}