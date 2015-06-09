
#include <syscalls.h>
#include <definitions.h>
#include <video.h>
#include <keyboard.h>
#include <lib.h>

int sys_read(FILE_DESCRIPTOR fileDescriptor, char * string, int length){
	int read = 0;

	int i = 0;

	read = waitBuffer(length);

	while (i < read) {
		string[i] = getCharFromBuffer();

		i++;

	}

	string[i] = 0;

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

void* sys_malloc(int len) {

	return malloc(len);

}

void* sys_calloc(int len) {

	return calloc(len);

}

void sys_free(void* m) {
	free(m);
}

void sys_keyboard_replace_buffer(char* s) {
	replaceLastWritten(s);
}

void sys_clear_screen() {
	video_clear_screen();
}