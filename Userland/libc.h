
#ifndef LIBC_HEADER
#define LIBC_HEADER

#include <definitions.h>

#define MAX_PRINTF_LEN 1024

void printf(char* fmt, ...) __attribute__ ((format (printf, 1, 2)));
void putchar(char c);
void* calloc(int len);
int strcmp(const char* s1, const char* s2);
void fprintf(FILE_DESCRIPTOR fd, char* fmt, ...) __attribute__ ((format (printf, 2, 3)));;
int strlen(char* str);
int getchar();
int scanf(char* c, int len);
char* itoc(int number);

#endif
