#include "idt.h"
#include "isr.h"
#include "paging.h"
#include "syscall.h"
#include "task.h"
#include "ext4.h"
#include "terminal.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

// Function declarations
void kernel_main();
void shell();
void execute_command(const char *command);
void print_prompt();
void change_color(const char *color);
char* fgets(char* str, int num, FILE* stream);

// Entry point for the kernel
void kernel_main() {
    terminal_initialize();

    // Print the welcome message
    printf("MySimpleOSKernel BETA Has Loaded\n");

    // Initialize other subsystems (IDT, ISRs, Paging, etc.)
    idt_init();
    isr_init();
    paging_init();
    syscall_init();
    task_init();

    // Start the shell
    shell();
}

// Simple shell implementation
void shell() {
    char command[256];

    while (true) {
        print_prompt();
        fgets(command, sizeof(command), stdin);
        execute_command(command);
    }
}

// Function to execute a given command
void execute_command(const char *command) {
    if (strncmp(command, "echo", 4) == 0) {
        printf("%s\n", command + 5);
    } else if (strncmp(command, "help", 4) == 0) {
        printf("Available commands: echo, help, exit, color\n");
    } else if (strncmp(command, "exit", 4) == 0) {
        printf("Exiting shell...\n");
        break;
    } else if (strncmp(command, "color", 5) == 0) {
        change_color(command + 7);
    } else {
        printf("Unknown command: %s\n", command);
    }
}

// Function to print the shell prompt
void print_prompt() {
    printf("root@/>> ");
}

// Function to change the terminal color
void change_color(const char *color) {
    if (strcmp(color, "yellow") == 0) {
        terminal_setcolor(VGA_COLOR_LIGHT_BROWN);
        printf("Wow Somebody Here Must Like Sunny Days\n");
    } else if (strcmp(color, "red") == 0 || strcmp(color, "blue") == 0 ||
               strcmp(color, "cyan") == 0 || strcmp(color, "pink") == 0) {
        if (strcmp(color, "red") == 0) {
            terminal_setcolor(VGA_COLOR_LIGHT_RED);
        } else if (strcmp(color, "blue") == 0) {
            terminal_setcolor(VGA_COLOR_LIGHT_BLUE);
        } else if (strcmp(color, "cyan") == 0) {
            terminal_setcolor(VGA_COLOR_LIGHT_CYAN);
        } else if (strcmp(color, "pink") == 0) {
            terminal_setcolor(VGA_COLOR_MAGENTA);
        }
        printf("Well That Was Unexpected\n");
    } else if (strcmp(color, "green") == 0) {
        terminal_setcolor(VGA_COLOR_LIGHT_GREEN);
        printf("Time To Be A Hacker From Hollywood\n");
    } else {
        printf("Unknown color: %s\n", color);
    }
}

// Simple implementation of fgets
char* fgets(char* str, int num, FILE* stream) {
    int i;
    for (i = 0; i < num - 1; i++) {
        char c = getchar();
        if (c == '\n' || c == '\r') {
            str[i] = '\0';
            break;
        }
        str[i] = c;
    }
    str[i] = '\0';
    return str;
}
