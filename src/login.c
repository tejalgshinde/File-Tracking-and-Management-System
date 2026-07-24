#include <stdio.h>
#include <string.h>

#include "login.h"
#include "utils.h"

#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"
#define MAX_ATTEMPTS   3

int loginUser(void) {
    char username[50];
    char password[50];
    int attempts = 0;

    clearScreen();
    printHeader("FILE TRACKING & MANAGEMENT SYSTEM - LOGIN");
    printf("Default credentials -> Username: admin | Password: admin123\n\n");

    while (attempts < MAX_ATTEMPTS) {
        getStringInput("Username: ", username, sizeof(username));
        getStringInput("Password: ", password, sizeof(password));

        if (strcmp(username, ADMIN_USERNAME) == 0 &&
            strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("\nLogin successful! Welcome, %s.\n", username);
            pauseScreen();
            return 1;
        }

        attempts++;
        printf("\nInvalid credentials. Attempts remaining: %d\n\n",
               MAX_ATTEMPTS - attempts);
    }

    printf("\nToo many failed attempts. Exiting...\n");
    return 0;
}
