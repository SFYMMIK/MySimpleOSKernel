#include <string.h>
#include "auth.h"

#define MAX_USERS 2

typedef struct {
    char username[256];
    char password[256];
} User;

User users[MAX_USERS] = {
    {"root", "root_password"},
    {"example-user", "user_password"}
};

char current_user[256] = "root";

bool authenticate(const char* username, const char* password) {
    for (int i = 0; i < MAX_USERS; i++) {
        if (strcmp(users[i].username, username) == 0 &&
            strcmp(users[i].password, password) == 0) {
            set_current_user(username);
            return true;
        }
    }
    return false;
}

bool is_root() {
    return strcmp(current_user, "root") == 0;
}

void set_current_user(const char* username) {
    strncpy(current_user, username, sizeof(current_user));
}

const char* get_current_user() {
    return current_user;
}
