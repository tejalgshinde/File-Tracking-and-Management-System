#include <stdio.h>
#include <string.h>

#include "file.h"
#include "utils.h"

void addFile(void) {
    FileRecord rec;
    FILE *fp;

    clearScreen();
    printHeader("ADD NEW FILE RECORD");

    rec.file_id = getNextFileId();
    printf("Assigned File ID: %d\n", rec.file_id);

    getStringInput("File Name       : ", rec.file_name, MAX_NAME);
    getStringInput("Department      : ", rec.department, MAX_DEPT);
    getStringInput("Handled By      : ", rec.handler, MAX_DEPT);

    strcpy(rec.status, "Pending");

    getCurrentDate(rec.date_created, MAX_DATE);
    strcpy(rec.last_updated, rec.date_created);

    getStringInput("Remarks         : ", rec.remarks, MAX_REMARKS);

    fp = fopen(DATA_FILE, "ab");
    if (fp == NULL) {
        printf("\nError: Could not open data file.\n");
        pauseScreen();
        return;
    }

    fwrite(&rec, sizeof(FileRecord), 1, fp);
    fclose(fp);

    printf("\nFile record added successfully with Status: Pending.\n");
    pauseScreen();
}
