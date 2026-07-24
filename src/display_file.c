#include <stdio.h>

#include "file.h"
#include "utils.h"

void displayAllFiles(void) {
    FILE *fp;
    FileRecord rec;
    int count = 0;

    clearScreen();
    printHeader("ALL FILE RECORDS");

    fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("\nNo records found. Data file does not exist yet.\n");
        pauseScreen();
        return;
    }

    printf("%-6s %-20s %-15s %-15s %-12s %-12s %-12s\n",
           "ID", "File Name", "Department", "Handled By", "Status",
           "Created", "Updated");
    printLine('-', 100);

    while (fread(&rec, sizeof(FileRecord), 1, fp) == 1) {
        printf("%-6d %-20.20s %-15.15s %-15.15s %-12.12s %-12s %-12s\n",
               rec.file_id, rec.file_name, rec.department, rec.handler,
               rec.status, rec.date_created, rec.last_updated);
        count++;
    }

    fclose(fp);

    if (count == 0) {
        printf("\nNo file records available.\n");
    } else {
        printLine('-', 100);
        printf("\nTotal records: %d\n", count);
    }

    pauseScreen();
}
