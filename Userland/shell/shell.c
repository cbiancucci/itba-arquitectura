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

		while ((*commandBuffer != ' ') && *commandBuffer != 0) {
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

	case 0: //print
		//command_echo(argc, argv);
		break;

	case 1: //help
		//command_help(argc, argv, commandList, commandCount);
		break;

	case 2: //time
		//command_time(argc, argv);
		break;

	case 3: //exit
		//command_exit();
		break;

	case 4: //clear
		//command_clear(argc);
		break;

	case 5: //screensaver
		//command_screensaver(argc, argv);
		break;

	default:

		printf("Command not found.");
	}

}