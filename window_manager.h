#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

void window_manager_initialize();
void create_window(const char* title, int x, int y, int width, int height);
void move_window(int window_id, int new_x, int new_y);
void window_manager_execute_program(const char *program_name);
int is_gui_program(const char *program_name);
void open_window(const char *program_name);
void update_window_manager();

#endif // WINDOW_MANAGER_H
