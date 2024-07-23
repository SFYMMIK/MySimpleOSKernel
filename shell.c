#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <dirent.h>
#include "shell.h"
#include "justaccompiler.h"
#include "auth.h"
#include "password_input.h"

#define MAX_COMMANDS 100
#define MAX_COMMAND_LENGTH 100
#define MAX_PATH_LENGTH 256

char* commands[MAX_COMMANDS];
int command_count = 0;
char current_directory[MAX_PATH_LENGTH] = "/";

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

    FILE* header = fopen("shell.h", "a");
    if (header == NULL) {
        perror("fopen");
        return;
    }

    while ((entry = readdir(dp))) {
        if (entry->d_type == DT_REG) { // If the entry is a regular file
            register_command(entry->d_name);
            fprintf(header, "void %s();\n", entry->d_name); // Write function prototype
        }
    }

    closedir(dp);
    fclose(header);
    printf("Commands registered from /prog/ directory and updated in shell.h.\n");
}

void execute_rse(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        return;
    }

    printf("Executing %s...\n", filename);
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Simulate executing the content of the file
        printf("%s", line);
    }

    fclose(file);
}

void execute_command(const char* command) {
    if (strncmp(command, "exec ", 5) == 0) {
        execute_rse(command + 5);
        return;
    }

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

void shell_prompt() {
    printf("%s@%s:%s >> ", get_current_user(), get_current_dir_name(), current_directory);
}

void change_directory(const char* path) {
    if (chdir(path) == 0) {
        getcwd(current_directory, sizeof(current_directory));
    } else {
        perror("chdir");
    }
}

void changeuser(const char* username) {
    char password[256];
    get_password(password, sizeof(password));
    if (authenticate(username, password)) {
        printf("User changed to %s.\n", username);
    } else {
        printf("Authentication failed.\n");
    }
}

void root_command() {
    char password[256];
    get_password(password, sizeof(password));
    if (authenticate("root", password)) {
        printf("User changed to root.\n");
    } else {
        printf("Authentication failed.\n");
    }
}

void root_u_command(const char* command) {
    char password[256];
    get_password(password, sizeof(password));
    if (authenticate("root", password)) {
        execute_command(command);
        set_current_user("example-user"); // Switch back to the non-root user
    } else {
        printf("Authentication failed.\n");
    }
}

void shell_init() {
    // Register initial built-in commands
    register_command("te");
    register_command("writecommands");
    register_command("compile");
    register_command("useradd");
    register_command("changeuser");
    register_command("root");

    // Register dynamic commands
    dynamic_commands();
}

void dynamic_commands() {
    // This function is a placeholder for dynamically registered commands
    // Each dynamically registered command should have a corresponding function in shell.c
}

void shell_run() {
    char command[256];

    shell_init();

    while (1) {
        shell_prompt();
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
        } else if (strncmp(command, "cd ", 3) == 0) {
            change_directory(command + 3); // Pass the directory to change_directory function
        } else if (strncmp(command, "changeuser ", 11) == 0) {
            changeuser(command + 11); // Pass the username to changeuser function
        } else if (strcmp(command, "root") == 0) {
            root_command();
        } else if (strncmp(command, "root -u ", 8) == 0) {
            root_u_command(command + 8); // Pass the command to root_u_command function
        } else {
            execute_command(command);
        }
    }
}
