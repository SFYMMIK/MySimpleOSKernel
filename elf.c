#include "elf.h"
#include "disk.h"
#include "memory.h"
#include "screen.h"

#define PAGE_SIZE 4096

static int read_elf_header(const char *path, elf_header_t *header) {
    if (read_disk(0, (char*)header, sizeof(elf_header_t)) != 0) {
        print_string("Failed to read ELF header\n");
        return -1;
    }
    return 0;
}

static int read_elf_program_header(const char *path, elf_program_header_t *ph, uint32_t offset) {
    if (read_disk(offset, (char*)ph, sizeof(elf_program_header_t)) != 0) {
        print_string("Failed to read ELF program header\n");
        return -1;
    }
    return 0;
}

int load_elf(const char *path) {
    elf_header_t header;
    if (read_elf_header(path, &header) != 0) {
        return -1;
    }

    if (header.e_ident[0] != 0x7F || header.e_ident[1] != 'E' || header.e_ident[2] != 'L' || header.e_ident[3] != 'F') {
        print_string("Not a valid ELF file\n");
        return -1;
    }

    for (int i = 0; i < header.e_phnum; i++) {
        elf_program_header_t ph;
        if (read_elf_program_header(path, &ph, header.e_phoff + i * header.e_phentsize) != 0) {
            return -1;
        }

        if (ph.p_type == 1) { // PT_LOAD
            char *mem = (char*)(uintptr_t)ph.p_vaddr;  // Properly cast to pointer
            memory_set((unsigned char*)mem, 0, ph.p_memsz);
            if (read_disk(ph.p_offset, mem, ph.p_filesz) != 0) {
                print_string("Failed to load ELF segment\n");
                return -1;
            }
        }
    }

    void (*entry_point)(void) = (void (*)(void))(uintptr_t)header.e_entry;  // Properly cast to function pointer
    entry_point();

    return 0;
}
