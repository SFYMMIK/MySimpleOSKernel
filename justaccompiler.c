#include "justaccompiler.h"
#include "filesystem.h"
#include "terminal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char* read_file(const char* filename) {
    // Read the file contents into a buffer
    // This function should be replaced with your actual file reading logic
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(length + 1);
    if (!buffer) {
        printf("Memory allocation error\n");
        fclose(file);
        return NULL;
    }
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

static void write_file(const char* filename, const char* data) {
    // Write the buffer contents to a file
    // This function should be replaced with your actual file writing logic
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return;
    }
    fwrite(data, 1, strlen(data), file);
    fclose(file);
}

void justaccompiler_compile(const char* filename) {
    char* source_code = read_file(filename);
    if (!source_code) {
        printf("Failed to read source file: %s\n", filename);
        return;
    }

    // Here we would parse and compile the source code
    // For simplicity, let's just echo the source code back as the "compiled" code
    // In a real compiler, this would involve several complex steps
    char* compiled_code = strdup(source_code);
    if (!compiled_code) {
        printf("Compilation failed for: %s\n", filename);
        free(source_code);
        return;
    }

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s.out", filename);
    write_file(output_filename, compiled_code);

    printf("Compilation successful! Output file: %s\n", output_filename);

    free(source_code);
    free(compiled_code);
}
