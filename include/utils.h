#ifndef UTILS_H
#define UTILS_H

/* General purpose helper functions used across the whole project */

void clearScreen(void);
void pauseScreen(void);
void printLine(char ch, int count);
void printHeader(const char *title);

void getStringInput(const char *prompt, char *buffer, int size);
int  getIntInput(const char *prompt);
void trimNewline(char *str);
void getCurrentDate(char *buffer, int size);

/* File-record helpers (implemented in utils.c, depend on file.h) */
int getNextFileId(void);
int fileExists(int file_id);

#endif /* UTILS_H */
