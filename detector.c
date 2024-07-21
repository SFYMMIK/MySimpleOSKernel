#include "detector.h"
#include "terminal.h"
#include <stdbool.h>
#include <io.h> // Assuming you have an io.h to interact with ports

#define PS2_STATUS_PORT 0x64
#define PS2_DATA_PORT 0x60

#define PS2_STATUS_OUTPUT_BUFFER 0x01
#define PS2_STATUS_INPUT_BUFFER 0x02

#define PS2_CMD_READ_BYTE0 0x20
#define PS2_CMD_WRITE_BYTE0 0x60

#define PS2_DEV_MOUSE 0xA9
#define PS2_DEV_KEYBOARD 0xAB

static bool mouse_detected = false;
static bool keyboard_detected = false;

static inline void io_wait(void) {
    // Wait for an I/O operation to complete
    asm volatile ("outb %%al, $0x80" : : "a"(0));
}

static int ps2_test_device(uint8_t command) {
    // Send command to PS/2 controller
    while (inb(PS2_STATUS_PORT) & PS2_STATUS_INPUT_BUFFER);
    outb(PS2_STATUS_PORT, command);

    // Wait for output buffer to be full
    while (!(inb(PS2_STATUS_PORT) & PS2_STATUS_OUTPUT_BUFFER));
    uint8_t result = inb(PS2_DATA_PORT);

    return result == 0x00; // 0x00 means no errors
}

void init_device_detectors(void) {
    mouse_detected = detect_mouse();
    keyboard_detected = detect_keyboard();
    
    if (mouse_detected) {
        terminal_writestring("Mouse detected.\n");
    } else {
        terminal_writestring("Mouse not detected.\n");
    }
    
    if (keyboard_detected) {
        terminal_writestring("Keyboard detected.\n");
    } else {
        terminal_writestring("Keyboard not detected.\n");
    }
}

int detect_mouse(void) {
    return ps2_test_device(PS2_DEV_MOUSE);
}

int detect_keyboard(void) {
    return ps2_test_device(PS2_DEV_KEYBOARD);
}
