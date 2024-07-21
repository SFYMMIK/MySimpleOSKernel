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

void mouse_initialize() {
    register_interrupt_handler(IRQ12, mouse_callback);
}

bool is_left_button_held() {
    return left_button_held;
}

bool is_left_button_clicked() {
    return left_button_clicked;
}
