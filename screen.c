#include "screen.h"
#include "io.h"

#define VGA_ADDRESS 0xB8000
#define WHITE_ON_BLACK 0x0F

static uint16_t *vga_buffer = (uint16_t*)VGA_ADDRESS;
static uint16_t cursor_position = 0;

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        vga_buffer[i] = ' ' | (WHITE_ON_BLACK << 8);
    }
    cursor_position = 0;
    update_cursor();
}

static void update_cursor() {
    outb(0x3D4, 14);
    outb(0x3D5, cursor_position >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor_position);
}

void print_string(const char *str) {
    while (*str) {
        if (*str == '\n') {
            cursor_position += 80 - cursor_position % 80;
        } else {
            vga_buffer[cursor_position++] = *str | (WHITE_ON_BLACK << 8);
        }
        str++;
    }
    update_cursor();
}
