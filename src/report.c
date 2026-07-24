#include <stdio.h>
#include <string.h>

#include "file.h"
#include "utils.h"
#include "report.h"

#define REPORT_FILE "data/summary_report.txt"

void generateSummaryReport(void) {
    FILE *fp, *out;
    FileRecord rec;
    int total = 0, pending = 0, process = 0, completed = 0, dispatched = 0, other = 0;

    clearScreen();
    printHeader("FILE STATUS SUMMARY REPORT");

    fp = fopen(DATA_FILE, "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        pauseScreen();
        return;
    }

    while (fread(&rec, sizeof(FileRecord), 1, fp) == 1) {
        total++;
        if (strcmp(rec.status, "Pending") == 0) pending++;
        else if (strcmp(rec.status, "In Process") == 0) process++;
        else if (strcmp(rec.status, "Completed") == 0) completed++;
        else if (strcmp(rec.status, "Dispatched") == 0) dispatched++;
        else other++;
    }
    fclose(fp);

    printf("Total Files       : %d\n", total);
    printf("Pending           : %d\n", pending);
    printf("In Process        : %d\n", process);
    printf("Completed         : %d\n", completed);
    printf("Dispatched        : %d\n", dispatched);
    printf("Other Status      : %d\n", other);

    out = fopen(REPORT_FILE, "w");
    if (out != NULL) {
        char datebuf[MAX_DATE];
        getCurrentDate(datebuf, MAX_DATE);

        fprintf(out, "File Tracking & Management System - Summary Report\n");
        fprintf(out, "Generated on: %s\n\n", datebuf);
        fprintf(out, "Total Files       : %d\n", total);
        fprintf(out, "Pending           : %d\n", pending);
        fprintf(out, "process        : %d\n", process);
        fprintf(out, "Completed         : %d\n", completed);
        fprintf(out, "Dispatched        : %d\n", dispatched);
        fprintf(out, "Other Status      : %d\n", other);

        fclose(out);
        printf("\nReport exported to %s\n", REPORT_FILE);
    }

    pauseScreen();
}
