#include "../include/definitions.h"
#include "../include/stdio.h"
#include "../include/syscalls.h"

#define ENTER			'\n'
#define TAB				'\t'
#define SPACE			' '
#define SCAN_ERROR		0

const char hexDigits [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

/* getc implementation */
int getc(int fd){
	byte c;
	return (__read(fd, &c, 1) == 1) ? (byte) c : EOF;
}

/* putc implementation */
int putc(int c, int fd){
	int ret;
	byte aux = BLUE_TEXT;
	byte character = (byte) c;

	if(c == TAB){
		putc(' ', fd);
		putc(' ', fd);
		putc(' ', fd);
	} else {
		ret = (__write(fd, &character, 1) == 1) ? c : EOF;
		__write(fd, &aux, 1);
	}
	return ret;
}