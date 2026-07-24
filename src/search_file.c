#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "file.h"
#include "utils.h"

static void printRecord(const FileRecord *rec) {
    printLine('-', 60);
    printf("File ID       : %d\n", rec->file_id);
    printf("File Name     : %s\n", rec->file_name);
    printf("Department    : %s\n", rec->department);
    printf("Handled By    : %s\n", rec->handler);
    printf("Status        : %s\n", rec->status);
    printf("Date Created  : %s\n", rec->date_created);
    printf("Last Updated  : %s\n", rec->last_updated);
    printf("Remarks       : %s\n", rec->remarks);
    printLine('-', 60);
}

static int containsIgnoreCase(const char *haystack, const char *needle) {
    char h[256], n[256];
    int i;

    for (i = 0; haystack[i] != '\0' && i < 255; i++) {
        h[i] = (char)tolower((unsigned char)haystack[i]);
    }
    h[i] = '\0';

    for (i = 0; needle[i] != '\0' && i < 255; i++) {
        n[i] = (char)tolower((unsigned char)needle[i]);
    }
    n[i] = '\0';

    return strstr(h, n) != NULL;
}

void searchFile(void) {
    FILE *fp;
    FileRecord rec;
    int choice, found = 0;

    clearScreen();
    printHeader("SEARCH FILE RECORD");

    printf("1. Search by File ID\n");
    printf("2. Search by File Name\n");
    choice = getIntInput("Enter choice: ");

    fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        pauseScreen();
        return;
    }

    if (choice == 1) {
        int id = getIntInput("Enter File ID to search: ");
        while (fread(&rec, sizeof(FileRecord), 1, fp) == 1) {
            if (rec.file_id == id) {
                printRecord(&rec);
                found = 1;
                break;
            }
        }
    } else if (choice == 2) {
        char name[MAX_NAME];
        getStringInput("Enter File Name (or part of it): ", name, MAX_NAME);
        while (fread(&rec, sizeof(FileRecord), 1, fp) == 1) {
            if (containsIgnoreCase(rec.file_name, name)) {
                printRecord(&rec);
                found = 1;
            }
        }
    } else {
        printf("\nInvalid choice.\n");
    }

    fclose(fp);

    if (!found && (choice == 1 || choice == 2)) {
        printf("\nNo matching record found.\n");
    }

    pauseScreen();
}
