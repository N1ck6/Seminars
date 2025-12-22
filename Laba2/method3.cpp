#include "method3.h"
void process_file_string() { 
    FILE* in = fopen("Laba1/input.txt", "r");
    FILE* out = fopen("Laba1/output.txt", "w");
    if (!in || !out) {
        if (in) fclose(in);
        if (out) fclose(out);
        return;
    }

    char buffer[1000] = "";
    fgets(buffer, sizeof(buffer), in);
    process_string(buffer);
    
    fputs(buffer, out);

    fclose(in);
    fclose(out);
}

char* input_string_calloc3() {
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