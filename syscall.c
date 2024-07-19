#include "syscall.h"

void init_syscalls() {
    // Initialize system calls
}

void syscall_handler(struct registers *r) {
    switch (r->eax) {
        case 0:
            print("Syscall: 0\n");
            break;
        default:
            print("Unknown syscall\n");
            break;
    }
}
