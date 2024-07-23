#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h> // For fixed width types

typedef uint32_t size_t; // Define size_t as an unsigned 32-bit integer

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
size_t strlen(const char* str);

#endif
