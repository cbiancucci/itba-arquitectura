
#ifndef LIBC_HEADER
#define LIBC_HEADER

#include <definitions.h>

#define MAX_PRINTF_LEN 1024



void printf(char* fmt, ...) __attribute__ ((format (printf, 1, 2)));
void putchar(char c);
void* calloc(int length);
void* malloc(int length);
int strcmp(const char* string1, const char* string2);
void fprintf(FILE_DESCRIPTOR fd, char* fmt, ...) __attribute__ ((format (printf, 2, 3)));;
int strlen(char* string);
int getchar();
int scanf(char* c, int length);
char* itoc(int number);
void clear_screen();
void exit();
/*


void free(void* m);
int strpos(char* s, char n);

char* itoc(int number) ;
int ctoi(char* c);
color_t get_color();
void set_color(vga_color fg, vga_color bg);
time_t* time();

char* strcpy(char* dest, char* src);
void * memset(void * destiny, int32_t c, uint64_t length);
bool string_numeric(char* str);
bool is_numeric(char c);
char* strcat(char* str1, char* str2);
void clear_screen();
void set_time(time_t * t);
void exit();

*/
#endif
