#include "terminal.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "vga.h"

// VGA terminal dimensions
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

// VGA terminal buffer
static uint16_t* const VGA_BUFFER = (uint16_t*) 0xB8000;
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

// Function to initialize the terminal
void terminal_initialize() {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_BUFFER;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

// Function to set a character at a specific position in the terminal
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

// Function to put a character on the terminal
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

// Function to write a string to the terminal
void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

// Function to write a null-terminated string to the terminal
void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

// Function to set the terminal color
void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

// VGA entry color
uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

// VGA entry
uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}
