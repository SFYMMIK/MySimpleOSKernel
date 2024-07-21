#ifndef USB_H
#define USB_H

#include <stdint.h>

// Initializes the USB system
void usb_init(void);

// Checks if a USB mouse is connected
int usb_detect_mouse(void);

// Checks if a USB keyboard is connected
int usb_detect_keyboard(void);

#endif // USB_H
