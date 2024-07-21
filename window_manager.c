#include "window_manager.h"
#include "terminal.h"

static int window_count = 0;
static int cursor_x = 40;
static int cursor_y = 12;

typedef struct {
    int x, y, width, height;
    char title[32];
    bool active;
} Window;

static Window windows[10];

void window_manager_initialize() {
    // Initialize some windows
    windows[0] = (Window){10, 5, 20, 10, "Window 1", true};
    window_count = 1;
    // Draw windows
    for (int i = 0; i < window_count; i++) {
        draw_window(&windows[i]);
    }
}

void window_manager_update_cursor(int x, int y) {
    // Clear the old cursor
    terminal_putentryat(' ', VGA_COLOR_LIGHT_GREY, cursor_x, cursor_y);
    cursor_x = x;
    cursor_y = y;
    // Draw the new cursor
    terminal_putentryat('.', VGA_COLOR_WHITE, cursor_x, cursor_y);
}

void window_manager_handle_click(int x, int y) {
    for (int i = 0; i < window_count; i++) {
        if (x >= windows[i].x && x < windows[i].x + windows[i].width &&
            y >= windows[i].y && y < windows[i].y + 1) {  // Assuming close button is on the title bar
            windows[i].active = false;
            clear_window(&windows[i]);
            return;
        }
    }
}

void draw_window(Window *win) {
    if (!win->active) return;

    for (int y = 0; y < win->height; y++) {
        for (int x = 0; x < win->width; x++) {
            if (y == 0 || y == win->height - 1 || x == 0 || x == win->width - 1) {
                terminal_putentryat('#', VGA_COLOR_LIGHT_GREY, win->x + x, win->y + y);
            } else if (y == 0 && x < strlen(win->title) + 2) {
                terminal_putentryat(win->title[x - 1], VGA_COLOR_LIGHT_GREY, win->x + x, win->y + y);
            } else {
                terminal_putentryat(' ', VGA_COLOR_LIGHT_GREY, win->x + x, win->y + y);
            }
        }
    }
}

void clear_window(Window *win) {
    for (int y = 0; y < win->height; y++) {
        for (int x = 0; x < win->width; x++) {
            terminal_putentryat(' ', VGA_COLOR_BLACK, win->x + x, win->y + y);
        }
    }
}
