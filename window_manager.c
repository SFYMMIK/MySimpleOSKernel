#include "window_manager.h"
#include "mouse.h"
#include "terminal.h"
#include <stdbool.h>

#define MAX_WINDOWS 10

typedef struct {
    int id;
    char title[256];
    int x, y;
    int width, height;
    bool active;
} window_t;

static window_t windows[MAX_WINDOWS];
static int window_count = 0;
static int active_window_id = -1;

void window_manager_initialize() {
    for (int i = 0; i < MAX_WINDOWS; i++) {
        windows[i].active = false;
    }
}

void create_window(const char* title, int x, int y, int width, int height) {
    if (window_count < MAX_WINDOWS) {
        window_t* window = &windows[window_count];
        window->id = window_count;
        strncpy(window->title, title, sizeof(window->title) - 1);
        window->x = x;
        window->y = y;
        window->width = width;
        window->height = height;
        window->active = true;
        window_count++;
        active_window_id = window->id;

        // Draw window border
        terminal_draw_rect(window->x, window->y, window->width, window->height);
        terminal_draw_string(window->title, window->x + 2, window->y + 1);
    }
}

void move_window(int window_id, int new_x, int new_y) {
    if (window_id >= 0 && window_id < MAX_WINDOWS && windows[window_id].active) {
        window_t* window = &windows[window_id];
        window->x = new_x;
        window->y = new_y;
        // Redraw window
        terminal_draw_rect(window->x, window->y, window->width, window->height);
        terminal_draw_string(window->title, window->x + 2, window->y + 1);
    }
}

void update_window_manager() {
    if (active_window_id != -1 && is_left_button_held()) {
        // Move the active window with the mouse
        int new_x = /* Calculate new X based on mouse position */;
        int new_y = /* Calculate new Y based on mouse position */;
        move_window(active_window_id, new_x, new_y);
    }
}
