#include "clock.h"
#include "terminal.h"
#include "window_manager.h"
#include <string.h>

void clock_set_time(void) {
    // Simplified time setting logic
    terminal_writestring("Enter new time (HH:MM:SS): ");
    // Handle user input to set the time
}

void clock_windowed(void) {
    open_window("clock");
}

void clock_execute_command(const char *command) {
    if (strcmp(command, "clock --set") == 0) {
        clock_set_time();
    } else if (strcmp(command, "clock --windowed") == 0) {
        clock_windowed();
    } else {
        terminal_writestring("Invalid clock command.\n");
    }
}
