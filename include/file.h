#ifndef FILE_H
#define FILE_H

#define DATA_FILE "data/records.dat"

#define MAX_NAME    100
#define MAX_DEPT    50
#define MAX_STATUS  30
#define MAX_REMARKS 200
#define MAX_DATE    20

typedef struct {
    int  file_id;
    char file_name[MAX_NAME];
    char department[MAX_DEPT];
    char handler[MAX_DEPT];
    char status[MAX_STATUS];
    char date_created[MAX_DATE];
    char last_updated[MAX_DATE];
    char remarks[MAX_REMARKS];
} FileRecord;

/* Core CRUD + tracking operations, one per source file */
void addFile(void);
void displayAllFiles(void);
void searchFile(void);
void updateFile(void);
void deleteFile(void);
void trackFile(void);
void sortFiles(void);

#endif /* FILE_H */
