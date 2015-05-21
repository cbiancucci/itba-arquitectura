/**********************
 kc.h
**********************/
#include "defs.h"

#ifndef _kc_
#define _kc_

/* Muestra la imagen de inicio */
void showSplashScreen();

/* Tiempo de espera */
void wait(int time);

/* Inicializa la entrada del IDT */
void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, 
						byte access, byte cero);

/* Imprime la hora y la temperatura en la esquina de la pantalla */
void firstLine();

/* Lee la hora del RTC y la devuelve en los parametros */
void getTime(byte*, byte*, byte*);

/* Inicializa el buffer de teclado */
BUFFER* initializeKeybBuffer();

/* Inicializa Shell */
void initializeShell(SHELL*);

#endif
