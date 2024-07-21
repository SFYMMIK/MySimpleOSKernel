#ifndef IO_H
#define IO_H

#include <stdint.h>

// Function to read a byte from an I/O port
static inline uint8_t inb(uint16_t port) {
    uint8_t result;
    __asm__("inb %1, %0" : "=a"(result) : "dN"(port));
    return result;
}

// Function to write a byte to an I/O port
static inline void outb(uint16_t port, uint8_t data) {
    __asm__("outb %1, %0" : : "dN"(port), "a"(data));
}

#endif // IO_H
