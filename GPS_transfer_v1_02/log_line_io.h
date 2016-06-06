#ifndef LOG_LINE_IO_H
#define LOG_LINE_IO_H

int getCol(char *dest, char *source, int n);
void getfll(char *dest, const char *source_file, const char *message);
void getall (const char *source_file, const char *message, char *dest_file);
void getnll (const char *source_file, const char *message, char *dest_file);
#endif
