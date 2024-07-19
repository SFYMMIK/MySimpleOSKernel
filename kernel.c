#include "types.h"
#include "screen.h"
#include "io.h"
#include "shell.h"
#include "memory.h"
#include "ext4.h"
#include "disk.h"
#include "process.h"
#include "elf.h"
#include "syscall.h"

void kernel_main() {
    clear_screen();
    print_string("Simple OS Booted\n");
    shell_run();
}
