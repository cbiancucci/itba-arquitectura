#include "../include/defs.h"
#include "../include/syscalls.h"
#include "../include/video.h"
#include "../include/kasm.h"

extern SHELL* shell;
char aux[SCREEN_SIZE-80*2];


/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen() {
	unsigned int i=SCREEN_START;
	byte aux[2]={' ', BLUE_TXT};
	while(i < (80*25*2))
	{
		__write(STDOUT, aux, 2);										
		i+=2;
	};
	shell->cursor=0;
	
	shell->lastEnter= shell->cursor;
}

void jumpLine() {
	int i;
	
	for (i = 80*2; i < SCREEN_SIZE; i++)
		aux[i-80*2] = shell->screen[i];

	for (i = 0; i < SCREEN_SIZE - 80*2; i++)
		shell->screen[i] = aux[i];
	
	for( ; i < SCREEN_SIZE; i++)
		shell->screen[i]=' ';
		
	shell->cursor-=80*2;

	repaintScreen();
}

void writeScreen(byte data) {
	__write(STDOUT, &data, 1); 											
}

void repaintLine(int lineNumber) {
	int i;
	int pos=shell->cursor;
	for(shell->cursor=i=80*2*lineNumber; i < 80*2*(lineNumber+1); ) {
		writeScreen(shell->screen[i]);
		i++;
		writeScreen(BLUE_TXT);
		i++;
	}
	shell->cursor=pos;
}
	
void repaintFirstLine() {
	int i;
	for(i = 0; i<SCREEN_START; i++) {
		shell->screen[i]=' ';
	}
	repaintLine(0);
}

void repaintScreen() {
    int i = 1;
    while(i < LINES) {
		repaintLine(i);
		i++;
    }
    
}

void update_cursor() {
	unsigned short position = shell->cursor;
	if (position != 0) {
			_outb(0x3D4, 0x0F);
			_outb(0x3D5, (unsigned char)(position/2));
			
			_outb(0x3D4, 0x0E);
			_outb(0x3D5, (unsigned char )(((position/2)>>8)));
	}
}
