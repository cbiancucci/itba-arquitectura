#define EOF -1

#define getChar()	getC(STDIN)
#define putChar()	putC((c), STDOUT)

#define EMPTY_BUFFER while(getChar() !='\n')

int getc(int fd);
int putc(int c, int fd);
void printf(char * format, ...);
int scanf(char * format, ...);
int isDigit(char);
int isSpace(char);
int stringToInt(char *, int);