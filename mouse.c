#include "mouse.h"
#include "isr.h"
#include "io.h"
#include "window_manager.h"

#define MOUSE_IRQ 12
#define MOUSE_PORT 0x60
#define MOUSE_STATUS_PORT 0x64

static int8_t mouse_cycle = 0;
static int8_t mouse_byte[3];
static int8_t mouse_x = 40;
static int8_t mouse_y = 12;

void mouse_write(uint8_t a_write) {
    // Wait to be able to send a command
    while (inb(MOUSE_STATUS_PORT) & 0x02);
    // Tell the mouse we are sending a command
    outb(MOUSE_STATUS_PORT, 0xD4);
    // Wait for the final part
    while (inb(MOUSE_STATUS_PORT) & 0x02);
    // Finally write
    outb(MOUSE_PORT, a_write);
}

uint8_t mouse_read() {
    // Wait for the mouse to be ready
    while (!(inb(MOUSE_STATUS_PORT) & 0x01));
    return inb(MOUSE_PORT);
}

void mouse_initialize() {
    // Enable the auxiliary mouse device
    outb(MOUSE_STATUS_PORT, 0xA8);
    // Enable the interrupts
    outb(MOUSE_STATUS_PORT, 0x20);
    uint8_t status = inb(MOUSE_PORT) | 2;
    outb(MOUSE_STATUS_PORT, 0x60);
    outb(MOUSE_PORT, status);
    // Use default settings
    mouse_write(0xF6);
    mouse_read();  // Acknowledge
    // Enable the mouse
    mouse_write(0xF4);
    mouse_read();  // Acknowledge

    // Register the mouse interrupt handler
    isr_register_interrupt_handler(MOUSE_IRQ, mouse_interrupt_handler);
}

void mouse_interrupt_handler() {
    switch(mouse_cycle) {
        case 0:
            mouse_byte[0] = inb(MOUSE_PORT);
            mouse_cycle++;
            break;
        case 1:
            mouse_byte[1] = inb(MOUSE_PORT);
            mouse_cycle++;
            break;
        case 2:
            mouse_byte[2] = inb(MOUSE_PORT);
            mouse_x += mouse_byte[1];
            mouse_y -= mouse_byte[2];  // Screen coordinates are usually Y-inverted
            if (mouse_x < 0) mouse_x = 0;
            if (mouse_y < 0) mouse_y = 0;
            if (mouse_x > 79) mouse_x = 79;
            if (mouse_y > 24) mouse_y = 24;
            window_manager_update_cursor(mouse_x, mouse_y);
            mouse_cycle = 0;
            break;
    }
}
