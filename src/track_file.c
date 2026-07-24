#include <stdio.h>
#include <string.h>

#include "file.h"
#include "utils.h"

#define TRACK_LOG "data/track_log.txt"

static void updateStatusAndLog(void) {
    FILE *fp;
    FileRecord rec;
    int id, found = 0;
    char newStatus[MAX_STATUS];
    char location[100];
    char remark[200];
    char datebuf[MAX_DATE];

    id = getIntInput("Enter File ID to track/update: ");

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

    printf("\nCurrent Status: %s\n", rec.status);
    getStringInput("Enter New Status (e.g. In Process/Dispatched/Completed): ",
                    newStatus, MAX_STATUS);
    getStringInput("Current Location/Department: ", location, sizeof(location));
    getStringInput("Remark: ", remark, sizeof(remark));

    strcpy(rec.status, newStatus);
    getCurrentDate(rec.last_updated, MAX_DATE);

    fseek(fp, -(long)sizeof(FileRecord), SEEK_CUR);
    fwrite(&rec, sizeof(FileRecord), 1, fp);
    fclose(fp);

    FILE *log = fopen(TRACK_LOG, "a");
    if (log != NULL) {
        getCurrentDate(datebuf, MAX_DATE);
        fprintf(log, "[%s] File ID %d | Status: %s | Location: %s | Remark: %s\n",
                datebuf, id, newStatus, location, remark);
        fclose(log);
    }

    printf("\nTracking entry recorded and status updated.\n");
    pauseScreen();
}

static void viewHistory(void) {
    int id = getIntInput("Enter File ID to view history: ");
    char line[512];
    char marker[32];
    int found = 0;

    FILE *log = fopen(TRACK_LOG, "r");
    if (log == NULL) {
        printf("\nNo tracking history available yet.\n");
        pauseScreen();
        return;
    }

    snprintf(marker, sizeof(marker), "File ID %d ", id);

    clearScreen();
    printHeader("FILE TRACKING HISTORY");

    while (fgets(line, sizeof(line), log) != NULL) {
        if (strstr(line, marker) != NULL) {
            printf("%s", line);
            found = 1;
        }
    }
    fclose(log);

    if (!found) {
        printf("\nNo history found for File ID %d.\n", id);
    }

    pauseScreen();
}

void trackFile(void) {
    int choice;

    clearScreen();
    printHeader("TRACK FILE MOVEMENT");
    printf("1. Update Status & Log Movement\n");
    printf("2. View Tracking History\n");
    choice = getIntInput("Enter choice: ");

    if (choice == 1) {
        updateStatusAndLog();
    } else if (choice == 2) {
        viewHistory();
    } else {
        printf("\nInvalid choice.\n");
        pauseScreen();
    }
}
