#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

void memory_set(uint8_t *dest, uint8_t val, size_t len);
void *kmalloc(size_t size);

#endif
