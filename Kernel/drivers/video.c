#include "video.h"

static char * screen = SCREEN_START;

void clear_screen(){
	int i;

	for(i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
		screen[i*2] = ' ';
	}
}