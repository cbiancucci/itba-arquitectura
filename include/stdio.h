#define EOF -1

#define getchar()		getc(STDIN)
#define putchar(c)		putc((c), STDOUT)

#define VACIA_BUFFER while(getchar()!='\n')

int getc(int fd);
int putc(int c, int fd);
void printf(char *fmt, ...);
int scanf(char *fmt, ...);
int isDigit(char);
int isSpace(char);
int strToInt(char*, int);
