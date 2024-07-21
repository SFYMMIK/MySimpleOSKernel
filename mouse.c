#include "mouse.h"
#include "isr.h"
#include "ports.h"
#include "terminal.h"
#include <stdbool.h>

static bool left_button_held = false;
static bool left_button_clicked = false;

static void mouse_callback(registers_t regs) {
    uint8_t status = port_byte_in(0x64);
    if (status & 0x01) {
        uint8_t mouse_data = port_byte_in(0x60);

        // Update button states
        left_button_held = mouse_data & 0x01;
        left_button_clicked = left_button_held && !(mouse_data & 0x02);

        // Displaying the output for debugging purposes
        if (left_button_held) {
            printf("lmb2\n");
        } else if (left_button_clicked) {
            printf("lmb1\n");
        }
    }
}

#include "mouse.h"
#include "io.h"

// Example implementation of mouse functions

static int mouse_x = 0;
static int mouse_y = 0;
static int left_button = 0;

void init_mouse() {
    // Initialize mouse
}

int is_left_button_pressed() {
    // Check if left mouse button is pressed
    return left_button == 1;
}

int is_left_button_held() {
    // Check if left mouse button is held
    return left_button == 2;
}

int get_mouse_x() {
    return mouse_x;
}

int get_mouse_y() {
    return mouse_y;
}
