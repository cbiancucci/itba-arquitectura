#include "video.h"

int video_current_row = 0;
int video_current_column = 0;
static color_t video_current_color = 0;

static void video_scroll();
static uint16_t video_get_full_char_from(int row, int col);
static void video_reset_color();
static void video_clear_line(int row);

void video_init(){
	video_reset_color();
	video_clear_screen();
}

// COLOR

void video_reset_color(){
	video_current_color = CREATE_COLOR(COLOR_WHITE, COLOR_BLACK);
}

void video_update_screen_color() {
	for (int c = 1; c < SCREEN_WIDTH * SCREEN_HEIGHT * 2; c += 2) {
		((uint8_t*)SCREEN_START)[c] = video_current_color;
	}
}

void video_set_color(color_t color){
	video_current_color = color;
}

void video_set_font_background_color(video_color font, video_color background){
	video_current_color = CREATE_COLOR(font, background);
}

void video_clear_screen(){
	for(int j = 0; j < SCREEN_WIDTH; j++){
		for(int i = 0; i < SCREEN_HEIGHT; i++){
			video_printc(' ');
		}
	}
	video_reset_cursor();
	video_update_screen_color();
}

static void video_clear_line(int row) {

	for (int i = 0; i < SCREEN_WIDTH; i++) {
		video_print_char_at(' ', row, i);
	}

	video_current_column = 0;
}

color_t video_get_color(){
	return video_current_color;
}

// PRINT

void video_printc(const char c){
	uint16_t char_16 = c;
	uint16_t color_16 = video_current_color;
	video_print_char(char_16 | (color_16 << 8));
}

void video_print_char(uint16_t c) {

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

void video_print_char_at(uint16_t c, int row, int col){
	SCREEN_START[row * SCREEN_WIDTH + col] = c;
}

void video_print_new_line(){
	video_current_column = 0;
	video_current_row++;

	if(video_current_row == SCREEN_HEIGHT) {
		video_scroll();
	}

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

	video_update_cursor();
}

void video_println(const char * string){

	if (video_current_column != 0) {
		video_print_new_line();
	}

	video_print_string(string);
	video_print_new_line();
}

// POSITION

void video_reset_cursor(){
	video_current_row = 0;
	video_current_column = 0;
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

// REFERENCE: http://wiki.osdev.org/Text_Mode_Cursor
void video_update_cursor() {
	unsigned short position = (video_current_row * 80) + video_current_column;
	// cursor LOW port to vga INDEX register
	outb(0x3D4, 0x0F);
	outb(0x3D5, (unsigned char)(position & 0xFF));
	// cursor HIGH port to vga INDEX register
	outb(0x3D4, 0x0E);
	outb(0x3D5, (unsigned char )((position >> 8) & 0xFF));
}