#ifndef FILESYSTEM_H
#define FILESYSTEM_H

void fs_initialize();
void create_default_directories(void);
void fs_execute_program(const char *name);
void fs_list_directory();
const char* fs_get_current_directory();

#endif // FILESYSTEM_H
