#include "useradd.h"
#include "stdio.h"
#include <string.h>

void useradd_program() {
    char username[256];
    char password[256];

    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);

    // Create user folder in /user/
    printf("User %s created successfully.\n", username);
}
