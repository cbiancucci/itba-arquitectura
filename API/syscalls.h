
#ifndef SYSCALLS_HEADER
#define SYSCALLS_HEADER

#include <definitions.h>

#define SYSCALL_RTC							1
#define SYSCALL_RTC_SET						2
#define SYSCALL_READ						3
#define SYSCALL_WRITE						4
#define SYSCALL_MALLOC						5
#define SYSCALL_CALLOC						6
#define SYSCALL_FREE						7
#define SYSCALL_VIDEO_CLR_INDEXED_LINE 		8
#define SYSCALL_KEYBOARD_REPLACE_BUFFER		9
#define SYSCALL_DELAY_SCREENSAVER			10
#define SYSCALL_SHOW_SCREENSAVER			11
#define SYSCALL_CLEAR_SCREEN				12
#define SYSCALL_EXIT						13


void sys_rtc_get(time_t* t);
void sys_rtc_set(time_t* t);
int sys_read(FILE_DESCRIPTOR fileDescriptor, char * string, int length);
void sys_write(FILE_DESCRIPTOR fileDescriptor, char * string, int length);
void* sys_malloc(int length);
void* sys_calloc(int length);
void sys_free(void* m);

void sys_init_screen();
void sys_clear_screen();

void sys_keyboard_replace_buffer(char* string);
void sys_set_delay_screensaver(uint64_t t);
void sys_show_screensaver();
void sys_exit();


#endif