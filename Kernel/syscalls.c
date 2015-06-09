
#include <syscalls.h>
#include <definitions.h>
#include <video.h>

int sys_read(FILE_DESCRIPTOR fileDescriptor, char * string, int length){
	int read = 0;
	return read;
}

void sys_write(FILE_DESCRIPTOR fileDescriptor, char * string, int length){
	switch(fileDescriptor) {
		case STDOUT:
			video_set_font_background_color(COLOR_WHITE, COLOR_BLACK);
			break;
		case STDERR:
			video_set_font_background_color(COLOR_RED, COLOR_BLACK);
			break;
	}
	video_print_string(string);
}

void sys_init_scree(){
	video_init();
}

void sys_clear_screen(){
	video_clear_screen();
}
