#ifndef EXT4_H
#define EXT4_H

#include <stdint.h>

void ext4_initialize();
int ext4_read_file(const char* path, uint8_t* buffer, uint32_t length);
int ext4_write_file(const char* path, const uint8_t* buffer, uint32_t length);

#endif // EXT4_H
