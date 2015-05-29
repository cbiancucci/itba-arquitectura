/******
	General Definitions
******/

#ifndef _defs_
#define _defs_

#define byte	unsigned char
#define word	short int
#define dword	int

#define TRUE	1
#define FALSE	0
#define NULL	0

/* File descriptors */
#define STDIN	0
#define STDOUT	1
#define STDERR	2

/** VIDEO ATTRIBUTES **/

/* Text color */
#define BLUE_TEXT		0x01 // Letras azules, fondo negro.
#define GREEN_TEXT		0x02 // Letras verdes, fondo negro.
#define CYAN_TEXT		0x03 // Letras celestes, fondo negro.
#define RED_TEXT		0x04 // Letras rojas, fondo negro.
#define PURPLE_TEXT		0x05 // Letras violetas, fondo negro.
#define YELLOW_TEXT		0x06 // Letras amarillas, fondo negro.
#define WHITE_TEXT		0x07 // Letras blancas, fondo negro.

/* Screen */
#define SCREEN_SIZE		4000 // 80 * 25 * 2.
#define SCREEN_START	160
#define MAX_LINE		250
#define LINES			25
#define COLUMNS			80

/* Buffer */
#define BUFFER_SIZE		1024











