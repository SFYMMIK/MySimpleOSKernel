#ifndef DETECTOR_H
#define DETECTOR_H

#include <stdint.h>

// Initializes the detectors for mouse and keyboard
void init_device_detectors(void);

// Checks if a mouse is connected
int detect_mouse(void);

// Checks if a keyboard is connected
int detect_keyboard(void);

#endif // DETECTOR_H
