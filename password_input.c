#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "password_input.h"

void get_password(char* password, size_t size) {
    struct termios oldt, newt;
    printf("Enter password: ");

    // Turn echoing off and fail if we can’t.
    if (tcgetattr(STDIN_FILENO, &oldt) != 0) {
        perror("tcgetattr");
        return;
    }
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &newt) != 0) {
        perror("tcsetattr");
        return;
    }

    // Read the password.
    if (fgets(password, size, stdin) == NULL) {
        perror("fgets");
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldt);
        return;
    }
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    // Restore terminal.
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &oldt) != 0) {
        perror("tcsetattr");
    }

    printf("\n");
}
