#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "te.h"

#define MAX_LINES 100
#define MAX_LINE_LENGTH 80
#define CTRL_KEY(k) ((k) & 0x1f)

void save_file(const char* filename, char* lines[], int num_lines) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < num_lines; i++) {
        fprintf(file, "%s", lines[i]);
        free(lines[i]);
    }
    fclose(file);
    printf("File saved.\n");
}

void te(const char* filename) {
    FILE* file;
    char* lines[MAX_LINES];
    char buffer[MAX_LINE_LENGTH];
    int num_lines = 0;
    int i;

    // Try to open the file
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("File does not exist. Do you want to create it? (y/n): ");
        char response = getchar();
        getchar(); // consume newline
        if (response == 'y' || response == 'Y') {
            file = fopen(filename, "w+");
            if (file == NULL) {
                printf("Error creating file.\n");
                return;
            }
        } else {
            return;
        }
    } else {
        // Read the file into the buffer
        while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL && num_lines < MAX_LINES) {
            lines[num_lines] = strdup(buffer);
            num_lines++;
        }
        fclose(file);
    }

    // Edit the file
    for (i = 0; i < num_lines; i++) {
        printf("%s", lines[i]);
    }
    printf("\nEditing (Ctrl + S to save, Ctrl + X to exit):\n");

    while (1) {
        int c = getchar();

        if (c == CTRL_KEY('s')) {
            save_file(filename, lines, num_lines);
        } else if (c == CTRL_KEY('x')) {
            save_file(filename, lines, num_lines);
            break;
        } else {
            ungetc(c, stdin); // put the character back to handle it normally
            if (fgets(buffer, MAX_LINE_LENGTH, stdin) != NULL) {
                lines[num_lines] = strdup(buffer);
                num_lines++;
            }
        }
    }
}
