#include "../include/defs.h"
#include "../include/stdio.h"
#include "../include/stdarg.h"
#include "../include/syscalls.h"


#define ENTER	'\n'
#define TAB		'\t'
#define SCAN_ERROR 0;

const char hexDigits[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

int getc(int fd) {
	byte c;
	return(__read(fd,&c,1) == 1) ? (byte) c : EOF;
}

int putc(int c, int fd) {
	int ret;
	byte aux=BLUE_TXT;
	byte ch=(byte)c;
	
	if(c == TAB) {
					putc(' ', fd);
					putc(' ', fd);
					putc(' ', fd);
					ret= c;
	}
	else {
		ret=(__write(fd,&ch,1) == 1) ? c : EOF;
		__write(fd,&aux,1);
	}
	return ret;
}

void printf(char *fmt, ...) {
	va_list ap; 
	char *p, *sval;
	int ival, i, v[32];
	unsigned int auxInt;
	va_start(ap, fmt); 
	
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		if(*p == '%') {
		switch (*++p) {
			case 'd': case 'i':
				ival = va_arg(ap, int);
				if(ival == 0)
					putchar('0');
				else {	
					if(ival < 0) {
						putchar('-');
						ival*=-1;
					}
					auxInt=ival;
					for(i=1; auxInt!=0; i*=10) 
						auxInt/=10;
					i/=10;
					while(i != 0) {
						putchar(((ival/i)%10)+'0');
						i/=10;
					}
				}
				break;
				
			case 'x': case 'X':
				ival = (unsigned int)va_arg(ap, int);
				printf("0x");	
				auxInt= ival;
				if(auxInt != 0) {
					i=0;
					while(auxInt) {
						v[i++]= auxInt%16;
						auxInt/=16;
					}
					i--;
					while(i>=0) {
						putchar(hexDigits[v[i]]);
						i--;
					}
				} else
					putchar('0');
				break;
			
			case 'b':
				ival = (unsigned int)va_arg(ap, int);
				auxInt= ival;
				printf("0b");
				if(auxInt != 0) {
					i=0;
					while(auxInt) {
						v[i++]= auxInt%2;
						auxInt/=2;
					}
					i--;
					while(i>=0) {
						printf("%d",v[i]);
						i--;
					}
				} else
					printf("%d",0);
				break;
				
			case 's':
				for (sval = va_arg(ap, char *); *sval; sval++)
					putchar(*sval);
				break;
			case 'c':
				ival = va_arg(ap, int);
				putchar(ival);
				p++;
				break;
			default:
				putchar(*p);
				break;
		}
	}
	}
	va_end(ap); 
}

int scanf(char *fmt, ...) {
	
	va_list ap; 
	int ival, i, error=FALSE, isNegative;
	int *ipointer;
	char *cpointer, *spointer;
	char c;
	int count = 0;
	va_start(ap, fmt); 
	
	while (*fmt && !error) {
		
		if (*fmt != '%') {
			if((c=getchar()) != *fmt) {
				error=TRUE;
			}	
			break;
		}
		if(*fmt == '%') {
			fmt++;
			switch (*fmt) {
				
				case 'd': case 'i':
				
					isNegative = FALSE;
					c=getchar();
					if(c == '-') {
						isNegative = TRUE;
						c=getchar();
					}
					i = 0;
					while(c && !isSpace(c)) {
						if(!isDigit(c) && !(c == '\n')) {
							error=TRUE;
							break;
						}
						else {
							cpointer[i]=c;
							i++;
							getchar();
						}
					}
					
					ival = strToInt(cpointer, i); 		
					if(isNegative)
						ival*=(-1);
					ipointer = va_arg(ap, int*);
					*ipointer = ival;
					count++;
					break;
				
				case 's':
					spointer = va_arg(ap, char *);
					i = 0;
					while((c=getchar()) && !isSpace(c)) {
						spointer[i] = c;
						i++;				
					}
					spointer[i] = 0;
					count++;
					break;
				
				case 'S':
					spointer = va_arg(ap, char *);
					i = 0;
					while((c=getchar()) !=EOF && c!= ENTER) {
						spointer[i] = c;
						i++;
					}
					spointer[i] = 0;
					count++;
					break;
					
				case 'c':
					cpointer = va_arg(ap, char *);
					*cpointer = getchar();
					count++;
						
					break;
					
				default:
					error=TRUE;
					break;
			}
		}
		fmt++;
	}

	va_end(ap); 
	if(error) {
		printf("There has been an error while reading. \n");
		return SCAN_ERROR;
	}
	
	return count;
}

int isDigit(char c) {

	if(c >= '0' && c<= '9')
		return TRUE;
	
	return FALSE;
}

int isSpace(char c) {
	
	if(c == '\n' || c == '\t' || c == ' ')
		return TRUE;
		
	return FALSE;	
}

int strToInt(char *str, int length) {
	
	int i, num = 0;

	for(i = 0; i < length; i++) {

		num *= 10;
		num += (str[i] - '0');
		
	}
	return num;
}
