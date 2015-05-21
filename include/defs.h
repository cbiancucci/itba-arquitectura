/***************************************************
  Defs.h
	
****************************************************/

#ifndef _defs_
#define _defs_

#define byte unsigned char
#define word short int
#define dword int

#define	TRUE			1
#define	FALSE			0
#define NULL			0

/* File Descriptors */
#define	STDIN			0
#define	STDOUT			1
#define STDERR			2

/* Atributo de video. */
#define WHITE_TXT 0x07	// Letras blancas, fondo negro
#define BLUE_TXT  0x09	// Letras azules, fondo negro

#define	SCREEN_SIZE 	4000
#define SCREEN_START	160
#define	BUFFER_SIZE		1024
#define MAX_LINE		256
#define LINES			25

/* Memory Pointers */
#define AUX_MEM			0x1000
#define BUFFER_MEM		0x3000

/* Flags para derechos de acceso de los segmentos */
#define ACS_PRESENT     0x80            /* segmento presente en memoria */
#define ACS_CSEG        0x18            /* segmento de codigo */
#define ACS_DSEG        0x10            /* segmento de datos */
#define ACS_READ        0x02            /* segmento de lectura */
#define ACS_WRITE       0x02            /* segmento de escritura */
#define ACS_IDT         ACS_DSEG
#define ACS_INT_386 	0x0E		/* Interrupt GATE 32 bits */
#define ACS_INT         ( ACS_PRESENT | ACS_INT_386 )

#define PROMPT			"Cosox:$> "
#define VID_MEM			0xb8000

#define ACS_CODE        (ACS_PRESENT | ACS_CSEG | ACS_READ)
#define ACS_DATA        (ACS_PRESENT | ACS_DSEG | ACS_WRITE)
#define ACS_STACK       (ACS_PRESENT | ACS_DSEG | ACS_WRITE)

#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

typedef int size_t;
typedef short int ssize_t;
typedef enum eINT_80 {WRITE=0, READ} tINT_80;
typedef enum eUSER {U_KERNEL=0, U_NORMAL} tUSERS;

/* Descriptor de segmento */
typedef struct {
  word limit,
       base_l;
  byte base_m,
       access,
       attribs,
       base_h;
} DESCR_SEG;


/* Descriptor de interrupcion */
typedef struct {
  word      offset_l,
            selector;
  byte      cero,
            access;
  word	    offset_h;
} DESCR_INT;

/* IDTR  */
typedef struct {
  word  limit;
  dword base;
} IDTR;

/* BUFFER */
typedef struct {
	byte	buff[BUFFER_SIZE];
	int		write_offset,
			read_offset;
} BUFFER;     

/* SHELL */
typedef struct {
	char	screen[SCREEN_SIZE],
			line_buffer[MAX_LINE];
	int		cursor,
			lastEnter;
} SHELL;

#endif

