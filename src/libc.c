#include "../include/kc.h"
#include "../include/kasm.h"
#include "../include/video.h"
#include "../include/syscalls.h"
#include "../include/stdio.h"


extern SHELL* shell;

enum {
      cmos_address = 0x70,
      cmos_data    = 0x71
};

/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}

static unsigned char get_RTC_register(int reg) {
	/* Fuente: http://wiki.osdev.org/ */
      _outb(cmos_address, reg);
      return _inb(cmos_data);
}

static int get_update_in_progress_flag() {
      _outb(cmos_address, 0x0A);
      return (_inb(cmos_data) & 0x80);
}

static void read_rtc(byte* hour, byte* minute, byte* second) {
	/* Fuente: http://wiki.osdev.org/ */
      unsigned char registerB;
 
	  while (get_update_in_progress_flag()); 
	  *second = get_RTC_register(0x00);
      *minute = get_RTC_register(0x02);
      *hour = get_RTC_register(0x04);
      registerB = get_RTC_register(0x0B);
 
      // Convert BCD to binary values if necessary
 
      if (!(registerB & 0x04)) {
            *second = (*second & 0x0F) + ((*second / 16) * 10);
            *minute = (*minute & 0x0F) + ((*minute / 16) * 10);
            *hour = ( (*hour & 0x0F) + (((*hour & 0x70) / 16) * 10) ) | (*hour & 0x80);
      }  
}

void getTime(byte* hs, byte* min, byte* secs) {
	read_rtc(hs, min, secs);
}

int getTemp() {
	int tempMax;
	int	tempRelativa;
	int tempAbs;
	
	tempMax= _tjunction();
	tempRelativa= _temp_relativa();
	
	tempAbs= tempMax-tempRelativa;
	
	return tempAbs;
}

void firstLine() {
	int aux, temp;
	byte hs, min, secs;
	
	getTime(&hs, &min, &secs);
	temp=getTemp(); 
	
	if(secs == 0)
		repaintFirstLine();
	aux = shell->cursor;
	shell->cursor= 106;
	printf("[ %d : %d : %d ] T: %d C", hs, min, secs, temp);
	shell->cursor= aux;
	
}

BUFFER* initializeKeybBuffer() {
	BUFFER* buffer = BUFFER_MEM;
	int i;
	for(i=0; i < BUFFER_SIZE; i++) {
		buffer->buff[i]=0;
	}
	buffer->write_offset=0;
	buffer->read_offset=0;
	return buffer;
}

