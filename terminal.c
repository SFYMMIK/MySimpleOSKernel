#include "terminal.h"
#include "justaccompiler.h"
#include "filesystem.h"
#include "mouse.h"
#include "window_manager.h"
#include "ext4.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
    printf("MySimpleOSKernel BETA Has Loaded\n");
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (++terminal_row == VGA_HEIGHT) {
                terminal_row = 0;
            }
        }
    }
}

void terminal_writestring(const char* data) {
    size_t datalen = strlen(data);
    for (size_t i = 0; i < datalen; i++) {
        terminal_putchar(data[i]);
    }
}

void handle_command(const char* command) {
    if (strncmp(command, "compile ", 8) == 0) {
        const char* filename = command + 8;
        justaccompiler_compile(filename);
    } else if (strcmp(command, "color --yellow") == 0) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_YELLOW, VGA_COLOR_BLACK));
        printf("Wow Somebody Here Must Like Sunny Days\n");
    } else if (strcmp(command, "color --red") == 0) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK));
        printf("Well That Was Unexpected\n");
    } else if (strcmp(command, "color --blue") == 0) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_BLUE, VGA_COLOR_BLACK));
        printf("Well That Was Unexpected\n");
    } else if (strcmp(command, "color --cyan") == 0) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_CYAN, VGA_COLOR_BLACK));
        printf("Well That Was Unexpected\n");
    } else if (strcmp(command, "color --pink") == 0) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK));
        printf("Well That Was Unexpected\n");
    } else if (strcmp(command, "color --green") == 0) {
        terminal_setcolor(vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK));
        printf("Time To Be A Hacker From Hollywood\n");
    } else if (strcmp(command, "useradd") == 0) {
        // Handle useradd command
        printf("Creating new user...\n");
        // Implement user creation logic here
    } else {
        printf("Unknown command: %s\n", command);
    }
}

void terminal_readcommand(char* buffer, size_t buffer_size) {
    size_t index = 0;
    while (1) {
        char c = getchar();
        if (c == '\n') {
            buffer[index] = '\0';
            return;
        } else if (index < buffer_size - 1) {
            buffer[index++] = c;
            terminal_putchar(c);
        }
    }
}
