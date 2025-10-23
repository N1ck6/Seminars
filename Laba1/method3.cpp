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