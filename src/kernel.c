#include "../include/kasm.h"
#include "../include/defs.h"
#include "../include/stdio.h"
#include "../include/kc.h"
#include "../include/video.h"


DESCR_INT idt[0xA];			/* IDT de 10 entradas*/
IDTR idtr;				/* IDTR */

SHELL* shell;
BUFFER* keyb_buff;

void int_08() {
	firstLine();
}


/**********************************************
kmain() 
Punto de entrada de cóo C.
*************************************************/
void
kmain() 
{
	
	
/* Borra la pantalla. */ 

	k_clear_screen();


/* CARGA DE IDT CON LA RUTINA DE ATENCION DE IRQ0    */

    setup_IDT_entry (&idt[0x08], 0x08, (dword)&_int_08_hand, ACS_INT, 0);
    setup_IDT_entry (&idt[0x09], 0x08, (dword)&_int_09_hand, ACS_INT, 0);
//	setup_IDT_entry (&idt[0x80], 0x08, (dword)&_int_80_hand, ACS_INT, 0);
	
/* Carga de IDTR */

	idtr.base = 0;  
	idtr.base +=(dword) &idt;
	idtr.limit = sizeof(idt)-1;
	
	_lidt (&idtr);	

	_Cli();
	
/* Habilito interrupcion de timer tick y teclado */

        _mascaraPIC1(0xFC);
        _mascaraPIC2(0xFF);
        
	_Sti();
	

	
	keyb_buff= initializeKeybBuffer();
	initializeShell(shell);
	

        while(1) 
        {
        }
	
}

