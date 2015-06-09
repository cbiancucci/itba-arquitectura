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

		printf("\nsarasa$ ");

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
		printf("Los comandos disponibles en Sarasa son:\n");
		printf("\tprint \t\t: Imprime un mensaje en pantalla.\n");
		printf("\thelp \t\t: Describe cada uno de los comandos disponibles en Sarasa.\n");
		printf("\ttime \t\t: Permite consultar o indicar la hora del sistema.\n");
		printf("\tclear\t\t: Limpia la pantalla.\n");
		printf("\tscreensaver: Activa o configura el salvapantallas.\n");
		printf("\texit \t\t: Finaliza el sistema.\n");

		printf("\nSi queres tener mas informacion de cada comando, proba con 'help COMANDO'\n");
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
			printf("\t PRINT Imprime un mensaje en pantalla, soportando espacios.\n");
			printf(" Ej: print Este es el TP de arqui, imprime el texto 'Este es el TP de arqui' en la pantalla.\n");
			break;

		case 1: // HELP
			printf("\t HELP Describe cada uno de los comandos disponibles en Sarasa.\n");
			printf("Si queres tener mas informacion de algun comando, proba con 'help COMANDO'\n");
			break;

		case 2: // TIME
			printf("\t TIME Permite consultar o indicar la hora del sistema.\n");
			printf("\tPodes indicarle a Sarasa la fecha y hora que desees a traves del comando 'time set HORAS MINUTOS SEGUNDOS DIA MES AÑO'\n");
			printf("\tAÑO debe tener 1 o 2 digitos y se le sumara 2000.\n");
			printf(" Ej: time set 18 30 32 10 6 15 setea la hora a las 18:30:32 del 10/06/2015.\n");
			break;

		case 3: // EXIT
			printf("\t EXIT Finaliza el sistema.\n");
			break;

		case 4: // CLEAR
			printf("\t CLEAR Cuando ya probaste mucho sarasa y no tenes mucho texto, este comando te ayuda a limpiar la pantalla para que puedas trabajar mas comodo\n");
			break;

		case 5: //screensaver
			printf("\t SCREENSAVER Activa el salvapantallas.\n");
			printf("\t Si queres configurar el tiempo que tarde el salvapantallas en activarse, podes hacerlo con 'screensaver set TIEMPO_EN_SEGUNDOS'.");
			break;
		default:
			printf("\nEl comando no esta disponible en sarasa.\n");
		}
	} else {
		printf("\nLos comandos en Sarasa constan de una palabra.\n");
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