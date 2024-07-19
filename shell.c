#include "shell.h"
#include "screen.h"
#include "io.h"
#include "process.h"
#include "memory.h"
#include "ext4.h"
#include "disk.h"
#include "syscall.h"

#define MAX_COMMAND_LENGTH 128

void execute_command(char *command) {
    // Example commands for demonstration
    if (strcmp(command, "clear") == 0) {
        clear_screen();
    } else if (strcmp(command, "help") == 0) {
        print_string("Supported commands: clear, help, echo\n");
    } else if (strncmp(command, "echo ", 5) == 0) {
        print_string(command + 5);
        print_string("\n");
    } else {
        print_string("Unknown command\n");
    }
}

void shell_run() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        print_string("> ");
        read_string(command, MAX_COMMAND_LENGTH);
        execute_command(command);
    }
}
