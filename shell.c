#include <stdio.h>
#include <string.h>
#include "shell.h"

#define MAX_COMMANDS 100
#define MAX_COMMAND_LENGTH 100

char* commands[MAX_COMMANDS];
int command_count = 0;

void register_command(const char* command) {
    if (command_count < MAX_COMMANDS) {
        commands[command_count] = strdup(command);
        command_count++;
    } else {
        printf("Command limit reached. Cannot register more commands.\n");
    }
}

void writecommands() {
    struct dirent* entry;
    DIR* dp = opendir("/prog");

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) { // If the entry is a regular file
            register_command(entry->d_name);
        }
    }

    closedir(dp);
    printf("Commands registered from /prog/ directory.\n");
}

void execute_command(const char* command) {
    for (int i = 0; i < command_count; i++) {
        if (strcmp(command, commands[i]) == 0) {
            // Construct the file path
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "/prog/%s", commands[i]);

            // Execute the program (simplified example, assumes the program is executable)
            FILE* fp = fopen(filepath, "r");
            if (fp) {
                // Simulate program execution
                printf("Executing %s...\n", filepath);
                fclose(fp);
            } else {
                printf("Failed to execute %s.\n", filepath);
            }
            return;
        }
    }

    printf("Command not found: %s\n", command);
}

void shell_run() {
    char command[256];

    // Register initial built-in commands
    register_command("te");
    register_command("writecommands");
    register_command("compile");
    register_command("useradd");

    while (1) {
        printf("shell> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strncmp(command, "te ", 3) == 0) {
            te(command + 3); // Pass the filename to te function
        } else if (strcmp(command, "writecommands") == 0) {
            writecommands();
        } else if (strncmp(command, "compile ", 8) == 0) {
            compile(command + 8); // Pass the filename to compile function
        } else if (strncmp(command, "useradd ", 8) == 0) {
            useradd(command + 8); // Pass the username to useradd function
        } else {
            execute_command(command);
        }
    }
}
