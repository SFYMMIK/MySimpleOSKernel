#include "stdio.h"
#include <stdlib.h>
#include <string.h>

// Simple function to compile a source file to a .rse executable
void compile(const char* filename) {
    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.rse", filename);

    FILE* source_file = fopen(filename, "r");
    if (source_file == NULL) {
        perror("fopen");
        return;
    }

    FILE* output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("fopen");
        fclose(source_file);
        return;
    }

    // Simple copy operation to simulate compilation
    char line[256];
    while (fgets(line, sizeof(line), source_file)) {
        fprintf(output_file, "%s", line);
    }

    fclose(source_file);
    fclose(output_file);
    printf("Compilation successful: %s created.\n", output_filename);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: compile <source_file.c>\n");
        return 1;
    }
    compile(argv[1]);
    return 0;
}
