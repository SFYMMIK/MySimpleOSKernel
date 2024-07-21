#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>

void terminal_initialize();
void terminal_setcolor(uint8_t color);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_clear();
void terminal_draw_cursor(int x, int y);
void terminal_draw_rect(int x, int y, int width, int height);
void terminal_draw_string(const char* str, int x, int y);

#endif // TERMINAL_H
