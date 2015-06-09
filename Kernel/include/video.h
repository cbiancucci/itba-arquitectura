
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

typedef enum{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
} video_color;

void video_init();
void video_reset_cursor();
void video_clear_screen();

void video_printc(const char c);
void video_print_new_line();
void video_print_string(const char * string);
void video_println(const char * string);

void video_set_color(color_t color);
void video_update_screen_color();
void video_set_font_background_color(video_color font, video_color background);

#endif
