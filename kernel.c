#include "idt.h"
#include "isr.h"
#include "paging.h"
#include "syscall.h"
#include "task.h"
#include "ext4.h"
#include "terminal.h"
#include "window_manager.h"
#include "filesystem.h"
#include "mouse.h"
#include "justaccompiler.h"
#include "clock.h"
#include "usb.h"
#include "detector.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "stdio.h"
#include <string.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

volatile uint16_t* vga_buffer = (uint16_t*)0xB8000;
size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color = 0x07; // Light grey on black

uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t)uc | (uint16_t)color << 8;
}


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

     terminal_initialize();

    // Initialize filesystem
    filesystem_initialize();

    // Initialize device detectors
    init_device_detectors();

    // Initialize USB system
    usb_init();

    // Print the welcome message
    printf("MySimpleOSKernel BETA Has Loaded\n");

    // Initialize other subsystems (IDT, ISRs, Paging, etc.)
    idt_init();
    isr_init();
    paging_init();
    syscall_init();
    task_init();

    // Initialize the window manager
    window_manager_initialize();

    // Initialize the filesystem
    fs_initialize();

    // Initialize the mouse
    mouse_initialize();

    // Initialize ext4 filesystem
    ext4_initialize();

    // Start the shell
    shell();

    if (usb_detect_mouse()) {
        terminal_writestring("USB mouse detected.\n");
        init_mouse();
    } else {
        terminal_writestring("USB mouse not detected.\n");
    }

    if (usb_detect_keyboard()) {
        terminal_writestring("USB keyboard detected.\n");
    } else {
        terminal_writestring("USB keyboard not detected.\n");
    }

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
        printf("Available commands: echo, help, exit, color, prog, dir, compile\n");
    } else if (strncmp(command, "exit", 4) == 0) {
        printf("Exiting shell...\n");
        break;
    } else if (strncmp(command, "color", 5) == 0) {
        change_color(command + 7);
    } else if (strncmp(command, "prog", 4) == 0) {
        fs_execute_program(command + 5);
    } else if (strncmp(command, "dir", 3) == 0) {
        fs_list_directory(command + 4);
    } else if (strncmp(command, "compile", 7) == 0) {
        char source_file[128];
        char output_file[128];
        sscanf(command + 8, "%s %s", source_file, output_file);
        compile(source_file, output_file);
    } else {
        printf("Unknown command: %s\n", command);
    }
}

// Function to print the prompt
void print_prompt() {
    printf("root@/>> ");
}

// Function to change text color based on the given color name
void change_color(const char *color) {
    if (strcmp(color, "yellow") == 0) {
        terminal_setcolor(VGA_COLOR_YELLOW);
        printf("Wow Somebody Here Must Like Sunny Days\n");
    } else if (strcmp(color, "red") == 0 ||
               strcmp(color, "blue") == 0 ||
               strcmp(color, "cyan") == 0 ||
               strcmp(color, "pink") == 0) {
        terminal_setcolor(VGA_COLOR_RED); // Modify as needed for other colors
        printf("Well That Was Unexpected\n");
    } else if (strcmp(color, "green") == 0) {
        terminal_setcolor(VGA_COLOR_GREEN);
        printf("Time To Be A Hacker From Hollywood\n");
    } else {
        printf("Unknown color: %s\n", color);
    }
}

// Simple fgets implementation
char* fgets(char* str, int num, FILE* stream) {
    // Implementation to read input from the terminal
    // ...
    return str;
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_row++;
        terminal_column = 0;
    } else {
        vga_buffer[terminal_row * VGA_WIDTH + terminal_column] = vga_entry(c, terminal_color);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
                terminal_row = 0; // Alternatively, implement scrolling here
            }
        }
    }
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

void terminal_initialize(void) {
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            vga_buffer[y * VGA_WIDTH + x] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void kernel_main(void) {
    terminal_initialize();
    
    // Initialize device detectors
    init_device_detectors();
    
    // Other kernel initialization code
    while (1) {
        // Main kernel loop
    }
}