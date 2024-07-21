#include "filesystem.h"
#include "terminal.h"
#include <string.h>
#include <stdio.h>

static const char *root_directory = "/";
static const char *prog_directory = "/prog/";
static const char *current_directory = "/";

void fs_initialize() {
    // Initialize the filesystem structure
}

const char* fs_get_current_directory() {
    return current_directory;
}

void fs_execute_program(const char *name) {
    if (strcmp(name, "useradd") == 0) {
        // Call useradd program
        useradd_program();
    } else {
        printf("Program not found: %s\n", name);
    }
}

void fs_list_directory() {
    // List directory contents
    if (strcmp(current_directory, "/") == 0) {
        printf("Directories:\n");
        printf("prog/\n");
        printf("user/\n");
    } else if (strcmp(current_directory, "/prog/") == 0) {
        printf("Programs:\n");
        printf("useradd\n");
    }
}

void useradd_program() {
    char username[256];
    char password[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);

    // Create user folder in /user/
    printf("User %s created successfully.\n", username);
}
