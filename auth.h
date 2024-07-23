#ifndef AUTH_H
#define AUTH_H

#include <stdbool.h>

bool authenticate(const char* username, const char* password);
bool is_root();
void set_current_user(const char* username);
const char* get_current_user();

#endif // AUTH_H
