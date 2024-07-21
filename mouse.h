#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>

void mouse_initialize();
void mouse_handler();

bool is_left_button_held();
bool is_left_button_clicked();

#endif // MOUSE_H
