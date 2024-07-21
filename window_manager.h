#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

void window_manager_initialize();
void create_window(const char* title, int x, int y, int width, int height);
void move_window(int window_id, int new_x, int new_y);

#endif // WINDOW_MANAGER_H
