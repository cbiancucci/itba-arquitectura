
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
#define SYSCALL_KEYBOARD_CATCH 				8
#define SYSCALL_VIDEO_CLR_INDEXED_LINE 		9
#define SYSCALL_KEYBOARD_REPLACE_BUFFER		10
#define SYSCALL_GET_COLOR					11
#define SYSCALL_SET_COLOR					12
#define SYSCALL_SET_TIME					13
#define SYSCALL_SET_KBD_DISTRIBUTION		14
#define SYSCALL_SCREENSAVER_TIMER			15
#define SYSCALL_SCREENSAVER_TRIGGER			16
#define SYSCALL_CLEAR_SCREEN				17
#define SYSCALL_EXIT						18


int sys_read(FILE_DESCRIPTOR fileDescriptor, char * string, int length);
void sys_write(FILE_DESCRIPTOR fileDescriptor, char * string, int length);
void sys_init_screen();
void sys_clear_screen();

void sys_rtc_get(time_t* t);
void sys_rtc_set(time_t* t);
void* sys_malloc(int length);
void* sys_calloc(int length);
void sys_free(void* m);
void sys_keyboard_replace_buffer(char* string);
void sys_set_screensaver_timer(uint64_t t);
void sys_screensaver_trigger();
void sys_exit();


#endif