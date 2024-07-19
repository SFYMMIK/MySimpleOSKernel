#include "process.h"
#include "memory.h"

static process_t *current_process = NULL;

void switch_task() {
    // Placeholder for task switching
}

void create_process(void (*entry_point)()) {
    process_t *new_process = (process_t*)kmalloc(sizeof(process_t));
    new_process->pid = 1; // Assign a unique PID
    new_process->eip = (uint32_t)entry_point;
    new_process->next = current_process;
    current_process = new_process;
}
