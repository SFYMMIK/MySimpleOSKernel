#include "usb.h"
#include "terminal.h"
#include "io.h"

#define USB_CONTROLLER_PORT 0x20

static int usb_send_command(uint8_t command) {
    // Sending command to USB controller
    while (inb(USB_CONTROLLER_PORT) & 0x2);
    outb(USB_CONTROLLER_PORT, command);
    return 0;
}

static int usb_read_data(void) {
    // Reading data from USB controller
    while (!(inb(USB_CONTROLLER_PORT) & 0x1));
    return inb(USB_CONTROLLER_PORT);
}

void usb_init(void) {
    // Initialize USB Controller
    usb_send_command(0x10); // Example command to initialize
}

int usb_detect_mouse(void) {
    usb_send_command(0xA8); // Example command to detect mouse
    return usb_read_data() == 0x03; // Assuming 0x03 is the mouse
}

int usb_detect_keyboard(void) {
    usb_send_command(0xA9); // Example command to detect keyboard
    return usb_read_data() == 0x04; // Assuming 0x04 is the keyboard
}
