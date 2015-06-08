
#ifndef VIDEO_HEADER
#define VIDEO_HEADER

#include <stdint.h>
#include <definitions.h>

#define SCREEN_START ((uint16_t*)0xB8000)

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define CREATE_COLOR(font, background) (color_t)((background << 4) | font)

typedef struct {
	int column;
	int row;
	uint16_t screen[SCREEN_HEIGHT*SCREEN_WIDTH];
	color_t color;
} screen_t;

void video_reset_cursor();
void video_update_screen_color();
void video_clear_screen();
void video_printc(const char c);
void video_print_new_line();
void video_print_string(const char * string);


#endif
