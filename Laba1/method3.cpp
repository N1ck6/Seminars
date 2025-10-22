#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void process_file_string(char str[], int max_size) {
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

    if (len + result_len + count_digits + 1 >= max_size) {
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
    FILE* input_file, * output_file;
    char str[256];

    input_file = fopen("Laba1/input.txt", "r");
    output_file = fopen("Laba1/output.txt", "w");
    if (input_file == NULL) {
        return 1;
    }

    if (fgets(str, 256, input_file) == NULL || output_file == NULL) {
        fclose(input_file);
        return 1;
    }

    fclose(input_file);

    int len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }

    process_file_string(str, 256);

    if (output_file == NULL) {
        return 1;
    }

    fputs(str, output_file);

    fclose(output_file);
}