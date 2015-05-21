#include "../include/defs.h"

/********************************** 
*
*  Kernel
*
***********************************/

#ifndef _kernel_
#define _kernel_

#define OS_PID	0

int (*player)(void);

/* __write
*
* Recibe como parametros:
* - File Descriptor
* - Buffer del source
* - Cantidad
*
**/
size_t __write(int fd, const byte * buffer, size_t count);

/* __read
*
* Recibe como parametros:
* - File Descriptor
* - Buffer a donde escribir
* - Cantidad
*
**/
size_t __read(int fd, byte * buffer, size_t count);

#endif
