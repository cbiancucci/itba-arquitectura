/*********************************************
kasm.h

************************************************/

#include "defs.h"


unsigned int    _read_msw();

void            _lidt (IDTR *idtr);

void		_mascaraPIC1 (byte mascara);  /* Escribe mascara de PIC1 */
void		_mascaraPIC2 (byte mascara);  /* Escribe mascara de PIC2 */

void		_Cli(void);        /* Deshabilita interrupciones  */
void		_Sti(void);	 /* Habilita interrupciones  */

void		_int_08_hand();      /* Timer tick */
void		_int_09_hand();		 /* Teclado */
void		_syscall(tINT_80, int, byte*, size_t);

void		_outb(unsigned short port, unsigned char val);
unsigned char _inb(unsigned short port);
void		_outl(unsigned short port, unsigned int val);
unsigned int _inl(unsigned short port);

int			_tjunction();
int			_temp_relativa();

void		_debug (void);


