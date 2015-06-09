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
void help_command(int argc, char** argv, char** cmd_list, int cmd_count);
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

	case 0: //print
		print_command(argc, argv);
		break;

	case 1: //help
		help_command(argc, argv, commandList, commandCount);
		break;

	case 2: //time
		time_command(argc, argv);
		break;

	case 3: //exit
		exit_command();
		break;

	case 4: //clear
		clear_command(argc);
		break;

	case 5: //screensaver
		screensaver_command(argc, argv);
		break;

	default:

		printf("Command not found.");
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

void help_command(int argc, char** argv, char** cmd_list, int cmd_count) {

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