#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "utils.h"

#define TEMP_FILE "data/temp.dat"

void deleteFile(void) {
    FILE *fp, *temp;
    FileRecord rec;
    int id, found = 0;
    char confirm[10];

    clearScreen();
    printHeader("DELETE FILE RECORD");

    id = getIntInput("Enter File ID to delete: ");

    fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        pauseScreen();
        return;
    }

    temp = fopen(TEMP_FILE, "wb");
    if (temp == NULL) {
        printf("\nError creating temporary file.\n");
        fclose(fp);
        pauseScreen();
        return;
    }

    while (fread(&rec, sizeof(FileRecord), 1, fp) == 1) {
        if (rec.file_id == id) {
            found = 1;
            continue; /* skip writing this record -> effectively deletes it */
        }
        fwrite(&rec, sizeof(FileRecord), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    if (!found) {
        printf("\nFile ID %d not found.\n", id);
        remove(TEMP_FILE);
        pauseScreen();
        return;
    }

    getStringInput("Are you sure you want to delete this record? (yes/no): ",
                    confirm, sizeof(confirm));

    if (strcmp(confirm, "yes") == 0 || strcmp(confirm, "y") == 0 ||
        strcmp(confirm, "Yes") == 0) {
        remove(DATA_FILE);
        rename(TEMP_FILE, DATA_FILE);
        printf("\nRecord deleted successfully.\n");
    } else {
        remove(TEMP_FILE);
        printf("\nDeletion cancelled.\n");
    }

    pauseScreen();
}
