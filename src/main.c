#include <stdio.h>
#include <stdlib.h>

#include "login.h"
#include "file.h"
#include "report.h"
#include "utils.h"

static void printMenu(void) {
    clearScreen();
    printHeader("FILE TRACKING & MANAGEMENT SYSTEM");
    printf("1. Add New File Record\n");
    printf("2. Display All File Records\n");
    printf("3. Search File Record\n");
    printf("4. Update File Record\n");
    printf("5. Delete File Record\n");
    printf("6. Track File Movement / Status\n");
    printf("7. Sort File Records\n");
    printf("8. Generate Summary Report\n");
    printf("9. Exit\n");
    printLine('-', 50);
}

int main(void) {
    int choice;

    if (!loginUser()) {
        return 0;
    }

    do {
        printMenu();
        choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1: addFile();             break;
            case 2: displayAllFiles();     break;
            case 3: searchFile();          break;
            case 4: updateFile();          break;
            case 5: deleteFile();          break;
            case 6: trackFile();           break;
            case 7: sortFiles();           break;
            case 8: generateSummaryReport(); break;
            case 9: printf("\nExiting... Thank you!\n"); break;
            case -1:
                printf("\nInput closed. Exiting...\n");
                break;
            default:
                printf("\nInvalid choice. Try again.\n");
                pauseScreen();
                break;
        }
    } while (choice != 9 && choice != -1);

    return 0;
}
