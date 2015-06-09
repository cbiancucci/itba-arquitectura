#include <stdint.h>
#include <syscalls.h>
#include <libc.h>
#include <definitions.h>

#define MAX_ARGS 				256
#define CMD_BUFFER_SIZE 		2*MAX_ARGS

#define LTRIM(str)			while (*(++commandBuffer) == ' ')

extern char bss;
extern char endOfBinary;

static int commandCount = 6;
static char *commandList[]={"print", "help", "time", "exit", "clear", "screensaver"};

// COMMANDS
void print_command(int argc, char** argv);
void help_command(int argc, char** argv);
void time_command(int argc, char** argv);
void screensaver_command(int argc, char** argv);
void exit_command();
void clear_command(int argc);

void parseCommand(char* commandBuffer);

int main() {

	static char buffer[CMD_BUFFER_SIZE] = {0};

	while (1) {
		printf(PROMPT);

		if (scanf(buffer, CMD_BUFFER_SIZE) == 0) {
			continue;
		}

		putchar('\n');
		parseCommand(buffer);
	}
	return 0xDEADBEEF;
}

void parseCommand(char* commandBuffer) {

	int argc = 0;
	char** argv = calloc(MAX_ARGS * sizeof(char*));

	if (*commandBuffer == ' ') {
		LTRIM(commandBuffer);
	}


	while (*commandBuffer != 0) {
		argv[argc] = calloc(CMD_BUFFER_SIZE * sizeof(char));

		char* pos = argv[argc];

		while ((*commandBuffer != ' ') && *commandBuffer != 0) {
			*pos = *commandBuffer;
			pos++;
			commandBuffer++;
		}

		if (*commandBuffer == ' ') {
			LTRIM(commandBuffer);
		}

		argc++;
	}

	int commandIdx = 0;
	
	for (; commandIdx < commandCount; commandIdx++) {
		if (strcmp(argv[0], commandList[commandIdx]) == 0) {
			break;
		}
	}

	switch (commandIdx) {

	case 0: // PRINT
		print_command(argc, argv);
		break;

	case 1: // HELP
		help_command(argc, argv);
		break;

	case 2: // TIME
		time_command(argc, argv);
		break;

	case 3: // EXIT
		exit_command();
		break;

	case 4: // CLEAR
		clear_command(argc);
		break;

	case 5: //screensaver
		screensaver_command(argc, argv);
		break;

	default:
		printf("El comando no fue encontrado.");
	}

}

void print_command(int argc, char** argv) {
	if (argc != 1) {
		for (int i = 1; i < argc; i++) {
			printf("%s ", argv[i]);
		}
	} else {
		printf("\n");
	}
}

void help_command(int argc, char** argv) {
	// Si vino solo help, listo todos los comandos 
	if (argc == 1) {
		printf("\nSarasa v1.0.0 (x64). GNU bash, version 0.0.1\n");
		printf("Desarrollado para ARQUITECTURA DE LAS COMPUTADORAS.\n");
		printf("@Zeitzen @matiasgualino @cbiancucci\n");
		printf("\nComandos disponibles:\n");
		printf("\tprint\t\t\tImprime un mensaje en pantalla.\n");
		printf("\thelp\t\t\t Describe cada uno de los comandos disponibles.\n");
		printf("\ttime\t\t\t Permite consultar o indicar la hora del sistema.\n");
		printf("\tclear\t\t\tLimpia la pantalla.\n");
		printf("\tscreensaver\t  Activa o configura el salvapantallas.\n");
		printf("\texit\t\t\t Finaliza el sistema.\n");

		printf("\nPara mas informacion de cada comando utilizar 'help [COMANDO]'\n");
	} else if (argc == 2) {
		// Si vino help y algo mas, tengo que ver si ese algo más es un comando de sarasa.
		int cmd = 0;
		for (; cmd < commandCount; cmd++) {
			if (strcmp(argv[1], commandList[cmd]) == 0) {
				break;
			}
		}

		switch (cmd) {

		case 0: // PRINT
			printf("\n PRINT Imprime un mensaje en pantalla, soportando espacios.\n");
			printf(" Uso: print [MENSAJE]\n");
			printf(" Ejemplo: print Este es el TP de arqui\n Se imprime el texto 'Este es el TP de arqui' en la pantalla.\n");
			break;

		case 1: // HELP
			printf("\n HELP Describe cada uno de los comandos disponibles en Sarasa.\n");
			printf(" Para mas informacion de cada comando utilizar 'help [COMANDO]'\n");
			break;

		case 2: // TIME
			printf("\n TIME Permite consultar o indicar la hora del sistema.\n");
			printf(" Uso: time set [HORAS] [MINUTOS] [SEGUNDOS] [DIA] [MES] [ANO]\n");
			printf(" Ejemplo: time set 18 30 32 10 6 15\n Configura la hora a las 18:30:32 del 10/06/2015.\n");
			printf(" * [ANO] soporta 2 digitos. Se suma 2000 de forma autmatica.\n");
			break;

		case 3: // EXIT
			printf("\n EXIT Finaliza el sistema.\n");
			break;

		case 4: // CLEAR
			printf("\n CLEAR Limpia la pantalla.\n");
			printf(" Cuando ya probaste mucho sarasa este comando te ayuda a limpiar la pantalla\n para que puedas trabajar mas comodo.\n");
			break;

		case 5: //screensaver
			printf("\n SCREENSAVER Activa el salvapantallas.\n");
			printf("\n Para configurar el tiempo de espera usar 'screensaver set [TIEMPO_EN_SEGUNDOS]'\n");
			break;
		default:
			printf("\n El comando no esta disponible en sarasa (proximamente...).\n");
		}
	} else {
		printf("\n Los comandos en Sarasa constan de una palabra (los desarrolladores son vagos).\n");
	}
}

void time_command(int argc, char** argv) {

}

void screensaver_command(int argc, char** argv) {

}

void exit_command() {
	clear_screen();
	exit();
}

void clear_command(int argc) {
	clear_screen();
}