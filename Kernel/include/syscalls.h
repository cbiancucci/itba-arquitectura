
#ifndef SYSCALLS_HEADER
#define SYSCALLS_HEADER

#include <definitions.h>

#define SYSCALL_EXIT						0
#define SYSCALL_READ						1
#define SYSCALL_WRITE						2
#define SYSCALL_CLEAR_SCREEN				3


int sys_read(FILE_DESCRIPTOR fileDescriptor, char * string, int length);
void sys_write(FILE_DESCRIPTOR fileDescriptor, char * string, int length);
void sys_init_screen();
void sys_clear_screen();

#endif