#ifndef PROCESS_H
#define PROCESS_H

#include "types.h"

typedef struct process {
    uint32_t pid;
    uint32_t eip;
    struct process *next;
} process_t;

void switch_task();
void create_process(void (*entry_point)());

#endif
