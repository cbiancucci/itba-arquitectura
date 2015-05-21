#include "../include/defs.h"
#include "../include/stdio.h"
#include "../include/syscalls.h"

#define NON_PRINT			0x0
#define	MAX_KEYS			0x59
#define LEFT_SHIFT_MAKE 	0x2A
#define RIGHT_SHIFT_MAKE 	0x36
#define CAPS_LOCK	 		0x3A
#define ALT_MAKE 			0x38
#define LEFT_SHIFT_BREAK 	0xAA
#define RIGHT_SHIFT_BREAK 	0xB6
#define ALT_BREAK 			0xB8
#define ENTER				0x1C
#define BACKSPACE			0x0E

static void	breakCode(int);
static byte getKey(int);
static int specialKey(int scancode);
void writeBuffer(byte);
void deleteFromBuffer();
void cmdInterpreter();

void 		k_clear_screen();
void 		update_cursor();

int 		shiftActivated = 0;
int 		capsLockActivated = 0;
int			altActivated = 0;
extern		SHELL* shell;
extern		BUFFER* keyb_buff;

char		keyboard[MAX_KEYS][2] = {
	
	//MAKECODE							SPECIAL KEY
	/*00*/		{NON_PRINT,NON_PRINT},
	/*01*/		{NON_PRINT,NON_PRINT},	//Esc
	/*02*/		{'1','!'},	
	/*03*/		{'2','@'},	
	/*04*/		{'3','#'},	
	/*05*/		{'4','$'},	
	/*06*/		{'5','%'},	
	/*07*/		{'6','^'},	
	/*08*/		{'7','&'},	
	/*09*/		{'8','*'},	
	/*0A*/		{'9','('},	
	/*0B*/		{'0',')'},	
	/*0C*/		{'-','_'},	
	/*0D*/		{'=','+'},	
	/*0E*/		{'\b','\b'},			//Backspace
	/*0F*/		{'\t','\t'},			//Tab
	/*10*/		{'q','Q'},	
	/*11*/		{'w','W'},	
	/*12*/		{'e','E'},	
	/*13*/		{'r','R'},	
	/*14*/		{'t','T'},	
	/*15*/		{'y','Y'},	
	/*16*/		{'u','U'},	
	/*17*/		{'i','I'},	
	/*18*/		{'o','O'},	
	/*19*/		{'p','P'},	
	/*1A*/		{'[','{'},	
	/*1B*/		{']','}'},	
	/*1C*/		{'\n','\n'},			//Enter	
	/*1D*/		{NON_PRINT,NON_PRINT},	//Left Ctrl
	/*1E*/		{'a','A'},	
	/*1F*/		{'s','S'},	
	/*20*/		{'d','D'},	
	/*21*/		{'f','F'},	
	/*22*/		{'g','G'},	
	/*23*/		{'h','H'},	
	/*24*/		{'j','J'},	
	/*25*/		{'k','K'},	
	/*26*/		{'l','L'},	
	/*27*/		{';',':'},		
	/*28*/		{'\'','"'},	
	/*29*/		{'`','~'},	
	/*2A*/		{NON_PRINT,NON_PRINT},	//Left Shift
	/*2B*/		{'\\','|'},	
	/*2C*/		{'z','Z'},	
	/*2D*/		{'x','X'},	
	/*2E*/		{'c','C'},	
	/*2F*/		{'v','V'},	
	/*30*/		{'b','B'},	
	/*31*/		{'n','N'},	
	/*32*/		{'m','M'},	
	/*33*/		{',','<'},	
	/*34*/		{'.','>'},	
	/*35*/		{'/','?'},	
	/*36*/		{NON_PRINT,NON_PRINT},	//Right Shift
	/*37*/		{'*','*'},				//Keypad *
	/*38*/		{NON_PRINT,NON_PRINT},	//Left Alt
	/*39*/		{' ',' '},				//Space
	/*3A*/		{NON_PRINT,NON_PRINT},	//Caps Lock
	/*3B*/		{NON_PRINT,NON_PRINT},	//F1
	/*3C*/		{NON_PRINT,NON_PRINT},	//F2
	/*3D*/		{NON_PRINT,NON_PRINT},	//F3
	/*3E*/		{NON_PRINT,NON_PRINT},	//F4
	/*3F*/		{NON_PRINT,NON_PRINT},	//F5
	/*40*/		{NON_PRINT,NON_PRINT},	//F6
	/*41*/		{NON_PRINT,NON_PRINT},	//F7
	/*42*/		{NON_PRINT,NON_PRINT},	//F8
	/*43*/		{NON_PRINT,NON_PRINT},	//F9
	/*44*/		{NON_PRINT,NON_PRINT},	//F10
	/*45*/		{NON_PRINT,NON_PRINT},	//Num Lock
	/*46*/		{NON_PRINT,NON_PRINT},	//Scroll Lock
	/*47*/		{NON_PRINT,NON_PRINT},	//Keypad 7
	/*48*/		{NON_PRINT,NON_PRINT},	//Keypad 8 // Up- Arrow
	/*49*/		{NON_PRINT,NON_PRINT},	//Keypad 9
	/*4A*/		{NON_PRINT,NON_PRINT},	//Keypad -
	/*4B*/		{NON_PRINT,NON_PRINT},	//Keypad 4 // Left- Arrow
	/*4C*/		{NON_PRINT,NON_PRINT},	//Keypad 5
	/*4D*/		{NON_PRINT,NON_PRINT},	//Keypad 6 // Right- Arrow
	/*4E*/		{NON_PRINT,NON_PRINT},	//Keypad +
	/*4F*/		{NON_PRINT,NON_PRINT},	//Keypad 1
	/*50*/		{NON_PRINT,NON_PRINT},	//Keypad 2 // Down-Arrow
	/*51*/		{NON_PRINT,NON_PRINT},	//Keypad 3
	/*52*/		{NON_PRINT,NON_PRINT},	//Keypad 0
	/*53*/		{NON_PRINT,NON_PRINT},	//Keypad . // Supr
	/*54*/		{NON_PRINT,NON_PRINT},	//Sys Req (AT)
	/*55*/		{'+','*'},	
	/*56*/		{'+','*'},	
	/*57*/		{NON_PRINT,NON_PRINT},	//F11
	/*58*/		{NON_PRINT,NON_PRINT}	//F12
	};	
	
	
	
void int_09 (int scancode) {

	byte character = 0;
  	if(!specialKey(scancode)) {
		if(scancode >= 0x58) {
			breakCode(scancode);
		} else {
			character = getKey(scancode);
		}
	
		if (character) {
			writeBuffer(character);
		}
	}
	update_cursor();
	
}

int isBufferEmpty() {
	return (keyb_buff->read_offset == keyb_buff->write_offset);
}

void emptyBuffer() {
	keyb_buff->read_offset=0;
	keyb_buff->write_offset=0;
}

void deleteFromBuffer() {
	if(keyb_buff->write_offset != keyb_buff->read_offset) {
		if(keyb_buff != 0)
			keyb_buff->write_offset--;
		else
			keyb_buff->write_offset=BUFFER_SIZE-1;
	}
}


void writeBuffer(byte character) {
	keyb_buff->buff[keyb_buff->write_offset] = character;
	putchar(keyb_buff->buff[keyb_buff->write_offset]);
	keyb_buff->write_offset++;
	if (keyb_buff->write_offset == BUFFER_SIZE) 
		keyb_buff->write_offset = 0;
		
	
}

static int isLetter(int scancode) {
	return ((scancode >= 0x10 && scancode <= 0x19) ||
			(scancode >= 0x1e && scancode <= 0x26) ||
			(scancode >= 0x2c && scancode <= 0x32));
}

byte getKey(int scancode) {
	switch(scancode) {
		case RIGHT_SHIFT_MAKE:
			shiftActivated = 1;
			return 0;
		case LEFT_SHIFT_MAKE:
			shiftActivated = 1;
			return 0;
		case CAPS_LOCK:
			capsLockActivated = !capsLockActivated;
			return 0;
	}
	
	if (isLetter(scancode)) {
		return keyboard[scancode][shiftActivated ^ capsLockActivated];
	}
	return keyboard[scancode][shiftActivated];
}

/* Retorna 1 si el scancode representa un caracter especial,
 * 0 si no */
static int specialKey(int scancode) {

	byte c = getKey(scancode);
	
	switch(scancode) {
		case ENTER:
			if(!isBufferEmpty()) {
				writeBuffer(c);
				cmdInterpreter();
				emptyBuffer();
			}
			putchar(c);
			printf("%s", PROMPT);
			shell->lastEnter = shell->cursor;
			return 1;
			
		case BACKSPACE:
			if(shell->cursor > shell->lastEnter + 1) {
				byte aux[2]={' ', BLUE_TXT};
				shell->cursor-=2;
				__write(STDOUT, aux, 2);								
				shell->cursor-=2;
				deleteFromBuffer();
			}
			return 1;
			

			
		default:
			return 0;
	}
}

static void breakCode(int scancode) {
  switch (scancode) {
    case LEFT_SHIFT_BREAK:
      shiftActivated = 0;
    case RIGHT_SHIFT_BREAK:
      shiftActivated = 0;
    case ALT_BREAK:
      altActivated = 0;
  }
}



