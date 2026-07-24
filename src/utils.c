#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "utils.h"
#include "file.h"

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen(void) {
    printf("\nPress Enter to continue...");
    fflush(stdout);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* discard until newline */
    }
}

void printLine(char ch, int count) {
    for (int i = 0; i < count; i++) {
        putchar(ch);
    }
    putchar('\n');
}

void printHeader(const char *title) {
    int len = (int)strlen(title);
    int width = len + 8;

    printLine('=', width);
    printf("    %s\n", title);
    printLine('=', width);
}

void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void getStringInput(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    fflush(stdout);

    if (fgets(buffer, size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    trimNewline(buffer);
}

int getIntInput(const char *prompt) {
    char temp[64];
    long value;

    while (1) {
        printf("%s", prompt);
        fflush(stdout);

        if (fgets(temp, sizeof(temp), stdin) == NULL) {
            /* stdin closed/EOF: signal the caller instead of looping forever */
            return -1;
        }
        trimNewline(temp);

        char *endptr;
        value = strtol(temp, &endptr, 10);

        if (endptr != temp && *endptr == '\0') {
            return (int)value;
        }

        printf("Invalid input. Please enter a valid number.\n");
    }
}

void getCurrentDate(char *buffer, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%d-%m-%Y", t);
}

int getNextFileId(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        return 1;
    }

    FileRecord rec;
    int maxId = 0;

    while (fread(&rec, sizeof(FileRecord), 1, fp) == 1) {
        if (rec.file_id > maxId) {
            maxId = rec.file_id;
        }
    }

    fclose(fp);
    return maxId + 1;
}

int fileExists(int file_id) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        return 0;
    }

    FileRecord rec;
    while (fread(&rec, sizeof(FileRecord), 1, fp) == 1) {
        if (rec.file_id == file_id) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}
