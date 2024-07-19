#ifndef DISK_H
#define DISK_H

#include "types.h"

int read_disk(uint32_t lba, char *buf, uint32_t size);

#endif
