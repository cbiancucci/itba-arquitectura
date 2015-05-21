#include "../include/defs.h"
#include "../include/kernel.h"
#include "../include/kasm.h"
#include "../include/video.h"

char* video = (char*) VID_MEM;
extern SHELL* shell;
extern BUFFER* keyb_buff;


size_t __write(int fd, const byte * buffer, size_t count) {
	
	int isEnter = FALSE;
	int i=-1;
	switch(fd) {
		case STDOUT:
			
			for(i=0; i < count && buffer[i] != 0; i++) {
				
				if(buffer[i] == '\n') {
					shell->cursor=shell->cursor+160-(shell->cursor%160)-1;
					isEnter=TRUE;
				}
				if(shell->cursor >= SCREEN_SIZE)
					jumpLine();
					
				if(!isEnter) {
					shell->screen[shell->cursor]=buffer[i];
					video[shell->cursor++]=buffer[i];
				}
			}
			break;
		
		default: 
			return -1;
	}
	return i;
	
}

size_t __read(int fd, byte * buffer, size_t count) {
	
	int i=-1;	
	switch(fd) {
		case STDIN:
		
			for(i=0; i < count && (keyb_buff->read_offset != keyb_buff->write_offset); i++) {
				if(keyb_buff->read_offset == BUFFER_SIZE) {
					keyb_buff->read_offset=0;
				}
				buffer[i]= keyb_buff->buff[keyb_buff->read_offset++];
			}
			break;
			
		default: 
			return -1;
	}
	return i;
	
}
/*
void int_80(tINT_80 fn, int fd, byte * buffer, size_t count) {
	
	switch(fn) {
		case WRITE:
			__write(fd,buffer,count);
			break;
			
		case READ:
			__read(fd,buffer,count);
			break;
			
		}
}
*/
