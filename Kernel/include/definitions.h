/******
	General Definitions
******/

#ifndef DEFINITIONS_HEADER
#define DEFINITIONS_HEADER

#include <stdint.h>

#define byte	unsigned char
#define word	short int
#define dword	int

#define TRUE	1
#define FALSE	0
#define NULL	0

#define EOF 	-1

/* File descriptors */
typedef enum {
	STDOUT,
	STDERR
} FILE_DESCRIPTOR;

/** VIDEO ATTRIBUTES **/
typedef uint8_t color_t;

/* Text color */
#define BLUE_TEXT		0x01 // Letras azules, fondo negro.
#define GREEN_TEXT		0x02 // Letras verdes, fondo negro.
#define CYAN_TEXT		0x03 // Letras celestes, fondo negro.
#define RED_TEXT		0x04 // Letras rojas, fondo negro.
#define PURPLE_TEXT		0x05 // Letras violetas, fondo negro.
#define YELLOW_TEXT		0x06 // Letras amarillas, fondo negro.
#define WHITE_TEXT		0x07 // Letras blancas, fondo negro.

/* Buffer */
#define BUFFER_SIZE		1024

/* Shell prompt */
#define PROMPT "sarasa$ "


#endif