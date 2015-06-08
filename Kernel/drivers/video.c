#include "video.h"

int video_current_row = 0;
int video_current_column = 0;
static color_t video_current_color = 0;

static void video_print_char(uint16_t c);
static void video_print_char_at(uint16_t c, int row, int col);
static void video_scroll();
static uint16_t video_get_full_char_from(int row, int col);
//static void video_reset_color();

void video_reset_cursor(){
	video_current_row = 0;
	video_current_column = 0;
}

void video_update_screen_color() {
	for (int c = 1; c < SCREEN_WIDTH * SCREEN_HEIGHT * 2; c += 2) {
		((uint8_t*)SCREEN_START)[c] = video_current_color;
	}
}

void video_set_color(int color){
	video_current_color = CREATE_COLOR(color, 0);
}

void video_clear_screen(){
	for(int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++){
		video_printc(' ');
	}
	video_reset_cursor();
	video_update_screen_color();
}

void video_printc(const char c){
	uint16_t char_16 = c;
	uint16_t color_16 = video_current_color;
	video_print_char(char_16 | (color_16 << 8));
}

static void video_print_char(uint16_t c) {

	video_print_char_at(c, video_current_row, video_current_column);

	video_current_column++;

	/*	Chequeamos que no se pase del ancho de pantalla.
		En ese caso ponemos la columna en 0 y hacemos un salto de linea.
	*/
	if (video_current_column == SCREEN_WIDTH) {
		video_current_column = 0;
		video_current_row++;
	}

	/*	Chequeamos que no se pase del alto de la pantalla.
		En ese caso hay que hacer un scroll.
	*/
	if (video_current_row == SCREEN_HEIGHT) {
		video_scroll();
	}
}

static void video_print_char_at(uint16_t c, int row, int col){
	SCREEN_START[row * SCREEN_WIDTH + col] = c;
}

void video_print_new_line(){
	video_current_column = 0;
	video_current_row++;
}

static void video_scroll(){
	
	for (int row = 1; row <= SCREEN_HEIGHT; row++) {
		for (int column = 0; column < SCREEN_WIDTH; column++) {
			uint16_t c = video_get_full_char_from(row, column);
			video_print_char_at(c, row - 1, column);
		}

	}
	video_current_row--;
	video_current_column = 0;
	video_update_screen_color();
}

static uint16_t video_get_full_char_from(int row, int col) {
	return SCREEN_START[row * SCREEN_WIDTH + col];
}

void video_print_string(const char * string) {
	while (*string != 0) {
		switch (*string) {
			case '\n':
				video_print_new_line();
				break;

			case '\t':
				video_print_string("    ");
				break;

			default:
				video_printc(*string);
				break;
		}
		string++;
	}

	//video_update_cursor();

}