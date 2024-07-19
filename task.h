#ifndef TASK_H
#define TASK_H

#include <stdint.h>

typedef struct task {
    uint32_t esp, ebp;
    struct task *next;
} task_t;

void init_tasking();
void switch_task();

#endif
