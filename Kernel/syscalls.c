
#include <syscalls.h>
#include <definitions.h>
#include <video.h>

int sys_read(FILE_DESCRIPTOR fileDescriptor, char * string, int length){
	int read = 0;
	return read;
}


void sys_write(FILE_DESCRIPTOR fileDescriptor, char * string, int length){

}

void sys_clear_screen(){
	video_clear_screen();
}