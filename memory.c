#include "memory.h"

void memory_set(uint8_t *dest, uint8_t val, size_t len) {
    for (size_t i = 0; i < len; i++) {
        dest[i] = val;
    }
}

void *kmalloc(size_t size) {
    static uint8_t *heap = (uint8_t*)0x100000;
    void *address = (void*)heap;
    heap += size;
    return address;
}
