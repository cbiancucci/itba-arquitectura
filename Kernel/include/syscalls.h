
#ifndef SYSCALLS_HEADER
#define SYSCALLS_HEADER

#include <definitions.h>

#define SYSCALL_READ						1
#define SYSCALL_WRITE						2
#define SYSCALL_MALLOC						3
#define SYSCALL_CALLOC						4
#define SYSCALL_FREE						5
#define SYSCALL_KEYBOARD_REPLACE_BUFFER		6
#define SYSCALL_CLEAR_SCREEN				7


int sys_read(FILE_DESCRIPTOR fileDescriptor, char * string, int length);
void sys_write(FILE_DESCRIPTOR fileDescriptor, char * string, int length);
void sys_clear_screen();
void* sys_malloc(int len);
void* sys_calloc(int len);
void sys_free(void* m);
void sys_keyboard_replace_buffer(char* s);

#endif