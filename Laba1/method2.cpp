#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void process_cstring(char str[]) {
    int len = strlen(str);

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

    int result_len = 0;
    long long temp_sum = total_sum;
    if (temp_sum == 0) {
        result_len = 1;
    }
    else {
        while (temp_sum > 0) {
            result_len++;
            temp_sum /= 10;
        }
    }

    int temp_count = count;
    int count_digits = 0;
    if (temp_count == 0) {
        count_digits = 1;
    }
    else {
        while (temp_count > 0) {
            count_digits++;
            temp_count /= 10;
        }
    }

    if (len + result_len + count_digits + 1 >= 256) {
        return;
    }

    int pos = len + result_len + count_digits + 1;
    str[pos] = '\0';
    pos--;

    if (count == 0) {
        str[pos--] = '0';
    }
    else {
        temp_count = count;
        while (temp_count > 0) {
            str[pos--] = (temp_count % 10) + '0';
            temp_count /= 10;
        }
    }

    str[pos--] = '&';

    if (total_sum == 0) {
        str[pos--] = '0';
    }
    else {
        temp_sum = total_sum;
        while (temp_sum > 0) {
            str[pos--] = (temp_sum % 10) + '0';
            temp_sum /= 10;
        }
    }
}

int main() {
    char str[256];

    printf("¬ведите строку: ");
    fgets(str, 256, stdin);

    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    process_cstring(str);

    printf(str);
}