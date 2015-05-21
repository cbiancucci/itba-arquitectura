#include "../include/defs.h"
#include "../include/video.h"
#include "../include/stdio.h"
#include "../include/string.h"


#define MAX_CMDS	8

extern BUFFER * keyb_buff;
char *			cmdList[MAX_CMDS] = {"echo", "help", "time", "lspci", 
									"cputemp", "test", "clear", "hack"};
							
enum CMDS { ECHO=0, HELP, TIME, LSPCI, CPUTEMP, TEST, CLEAR, HACK };

void getTime(byte*, byte*, byte*);
int isBufferEmpty();
void emptyBuffer();
void lspci();
int getTemp();

void initializeShell(SHELL* shell) {
	
	char *prompt = PROMPT;
	int i, j;
	
	for(i=0; i<SCREEN_SIZE; i++) {
		shell->screen[i]=' ';
	}
	
	i=SCREEN_START;
	j=0;
	while(prompt[j]) {
		shell->screen[i]=prompt[j++];
		i+=2;
	}
	
	shell->lastEnter = i;
	shell->cursor=i;
	
	repaintScreen();
	update_cursor();
}

static void execEcho() {
	int aux=0;
	char *s = AUX_MEM;
	if(keyb_buff->buff[keyb_buff->read_offset] == '\n') 
		return;
	aux= scanf("%S", s);
	if(aux)
		printf("%s", s);
	else
		printf("Error");
}

static void execHelp() {
	putchar('\n');putchar('\t');
	printf("Help:");
	putchar('\n');
	putchar('\n'); putchar('\t');
	printf("echo [args]               Prints [args] on screen");
	putchar('\n'); putchar('\t');
	printf("help                      Displays help on screen");
	putchar('\n'); putchar('\t');
	printf("time                      Displays current time on screen");
	putchar('\n'); putchar('\t');
	printf("lspci                     Lists PCI devices information");
	putchar('\n'); putchar('\t');
	printf("cputemp	                Displays current CPU temperature on screen");
	putchar('\n'); putchar('\t');
	printf("test                      Raises the CPU temperature");
	putchar('\n'); putchar('\t');
	printf("clear                     Clears screen");
	putchar('\n');
}

static void execTime() {
	byte hs, min, seg;
	getTime(&hs, &min, &seg);
	printf("[ %d : %d : %d ]", hs, min, seg);
}

static void exec_lspci() {
	lspci();
}

static void exec_cputemp() {
	printf("Temperature: %d C", getTemp());
}

static void execTest() {
	int i, j;
	
	int flag = TRUE;
	
	printf("Raising temperature..."); putchar('\n');
	
	for(i=2 ; i < 65536*2 && i ; i++) {
		
		flag = TRUE;
		
		for(j = 2 ; j <= i && j ; j++) {
			if(i%j == 0 && i != j && i && j)
				flag = FALSE;
		}
		
		if(flag == TRUE) {
			printf("%d is a prime number.", i); putchar('\n');
		}
	}
}

static void execClear() {
	k_clear_screen();
}

static void execHack() {
	printf("                               ");putchar('\n');
	printf("             /\\\\                ");putchar('\n');
	printf("            /  \\\\               ");putchar('\n');
	printf("           /    \\\\              ");putchar('\n');
	printf("          /______\\\\             ");putchar('\n');
	printf("         /\\\\      /\\\\            ");putchar('\n');
	printf("        /  \\\\    /  \\\\           ");putchar('\n');
	printf("       /    \\\\  /    \\\\          ");putchar('\n');
	printf("      /______\\\\/______\\\\         ");putchar('\n');
	printf("                               ");putchar('\n');
	printf("             lol               ");putchar('\n');putchar('\n');
}

static void executeCmd(int cmd) {
	
	switch(cmd) {
		
		case ECHO:
			execEcho();
			break;
			
		case HELP:
			execHelp();
			break;
		
		case TIME:
			execTime();
			break;
			
		case LSPCI:
			exec_lspci();
			break;
		
		case CPUTEMP:
			exec_cputemp();
			break;
			
		case TEST:
			execTest();
			break;
			
		case CLEAR:
			execClear();
			break;
			
		case HACK:
			execHack();
			break;
			
		default:
			printf("Error executing command");
	}
}
	
void cmdInterpreter() {
	int i, found=FALSE, count=0;
	char * cmd= 0x2000;
	
	count=scanf("%s", cmd);
	
	if(count) {
		for(i=0; i < MAX_CMDS && !found; i++) {
			if(strcmp(cmdList[i], cmd) == 0)
				found= TRUE;
		}
		if(!found) {
			printf("%s: Command not found", cmd);
		} else {
			i--;
			executeCmd(i);
		}
	} else
		printf("Error");
}


