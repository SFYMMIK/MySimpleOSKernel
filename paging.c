#include "paging.h"

uint32_t *page_directory;
uint32_t *first_page_table;

void init_paging() {
    page_directory = (uint32_t*)0x9C000;
    first_page_table = (uint32_t*)0x9D000;

    for (int i = 0; i < 1024; i++) {
        page_directory[i] = 0x00000002;
    }

    for (int i = 0; i < 1024; i++) {
        first_page_table[i] = (i * 0x1000) | 3;
    }

    page_directory[0] = ((uint32_t)first_page_table) | 3;

    load_page_directory(page_directory);
    enable_paging();
}
