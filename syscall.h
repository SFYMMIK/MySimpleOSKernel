#ifndef SYSCALL_H
#define SYSCALL_H

#include <stdint.h>

void init_syscalls();
void syscall_handler(struct registers *r);

#endif
