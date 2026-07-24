#include <stdio.h>
#include <string.h>

#include "file.h"
#include "utils.h"

void updateFile(void) {
    FILE *fp;
    FileRecord rec;
    int id, found = 0;
    char buffer[MAX_REMARKS];

    clearScreen();
    printHeader("UPDATE FILE RECORD");

    id = getIntInput("Enter File ID to update: ");

    fp = fopen(DATA_FILE, "rb+");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        pauseScreen();
        return;
    }

    while (fread(&rec, sizeof(FileRecord), 1, fp) == 1) {
        if (rec.file_id == id) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nFile ID %d not found.\n", id);
        fclose(fp);
        pauseScreen();
        return;
    }

    printf("\nCurrent details:\n");
    printf("File Name  : %s\n", rec.file_name);
    printf("Department : %s\n", rec.department);
    printf("Handled By : %s\n", rec.handler);
    printf("Status     : %s\n", rec.status);
    printf("Remarks    : %s\n", rec.remarks);
    printf("\nLeave a field blank to keep its existing value.\n\n");

    getStringInput("New File Name  : ", buffer, MAX_NAME);
    if (strlen(buffer) > 0) strcpy(rec.file_name, buffer);

    getStringInput("New Department : ", buffer, MAX_DEPT);
    if (strlen(buffer) > 0) strcpy(rec.department, buffer);

    getStringInput("New Handled By : ", buffer, MAX_DEPT);
    if (strlen(buffer) > 0) strcpy(rec.handler, buffer);

    getStringInput("New Status     : ", buffer, MAX_STATUS);
    if (strlen(buffer) > 0) strcpy(rec.status, buffer);

    getStringInput("New Remarks    : ", buffer, MAX_REMARKS);
    if (strlen(buffer) > 0) strcpy(rec.remarks, buffer);

    getCurrentDate(rec.last_updated, MAX_DATE);

    fseek(fp, -(long)sizeof(FileRecord), SEEK_CUR);
    fwrite(&rec, sizeof(FileRecord), 1, fp);

    fclose(fp);

    printf("\nRecord updated successfully.\n");
    pauseScreen();
}
