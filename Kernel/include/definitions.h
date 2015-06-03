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
#define SCREEN_SIZE		4000 // 80 * 25 * 2 (letra y fondo).
#define SCREEN_START	160
#define MAX_LINE		250
#define LINES			25
#define COLUMNS			80

/* Buffer */
#define BUFFER_SIZE		1024

/* Shell prompt */
#define PROMPT "sarasa$ "


typedef int size_t;
typedef short int ssize_t;
typedef enum enum_INT_80 {WRITE = 0, READ} INT_80;
typedef enum enum_SPACE {KERNEL = 0, USER} SPACE;

/* BUFFER */
typedef struct {
	byte	buff[BUFFER_SIZE];
	int 	write_offset,
			read_offset;
} BUFFER;


/* SHELL */
typedef struct {
	char	screen[SCREEN_SIZE],
			line_buffer[MAX_LINE];
	int 	cursor,
			lastEnter;
} SHELL;

/* Segment Descriptor */
typedef struct {
	word	limit,
			base_l;
	byte	base_m,
			access,
			attributes,
			base_h;
} SEGMENT_DESCRIPTOR;

/* Interrupt Descriptor */
typedef struct {
	word	offset_l,
			offset_h,
			selector;
	byte	zero,
			access;
} INTERRUPT_DESCRIPTOR;

/* Interrupt Descriptor Table */
typedef struct {
	word	limit;
	dword	base;
} IDT;
