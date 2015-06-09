#include <stdarg.h>
#include <definitions.h>
#include <syscalls.h>
#include <libc.h>

void* calloc(int length) {
	return sys_calloc(length);
}

void* malloc(int length) {
	return sys_malloc(length);
}

static void vfprintf(FILE_DESCRIPTOR fd, char* fmt, va_list ap) {

	char* str = calloc(MAX_PRINTF_LEN);
	int i = 0;
	int j = 0;

	while (fmt[i] != 0 && i < MAX_PRINTF_LEN - 1) {

		if (fmt[i] == '%') {

			bool flag_zero = FALSE;
			uint32_t width = 0;

			i++;
			if (fmt[i] == 0) {
				str[j] = fmt[i];
				break;

			} else if (fmt[i] == '%') {

				str[j] = fmt[i];
				j++;
				i++;

			} else {
				bool flag;
				do {

					flag = FALSE;
					switch (fmt[i]) {
					case 's': {
						char* arg = va_arg(ap, char*);
						int k = 0;

						while (arg[k] != 0) {
							str[j] = arg[k];
							j++;
							k++;
						}

						i++;
						break;
					}

					case 'i': {

						int arg = va_arg(ap, int);

						char* number = itoc(arg);

						int k = 0;

						int numlen = strlen(number);

						if (numlen < width) {

							char chartowrite;
							int numtowrite = width - numlen;

							if (flag_zero) {
								chartowrite = '0';

							} else {
								chartowrite = ' ';
							}

							for (int i = 0; i < numtowrite; i++) {
								str[j] = chartowrite;
								j++;
							}

						}

						while (number[k] != 0) {
							str[j] = number[k];
							j++;
							k++;
						}

						i++;
						break;

					}

					case 'c': {

						char arg = (char)va_arg(ap, int);

						str[j] = arg;
						j++;
						i++;
						break;

					}
					case '0': {
						if (!flag_zero) {
							flag_zero = TRUE;
							i++;
							flag = TRUE;
							break;
						}
						break;
					}

					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9': {
						width = fmt[i] - '0';
						i++;
						flag = TRUE;
						break;
					}

					}

				} while (flag);

			}

		} else if (fmt[i] != 0) {
			str[j] = fmt[i];
			j++;
			i++;
		} else {
			str[j] = fmt[i];
			break;
		}

	}
	sys_write(fd, str, j);
}

void printf(char* fmt, ...) {

	va_list ap;
	va_start(ap, fmt);

	vfprintf(STDOUT, fmt, ap);

	va_end(ap);

}

void putchar(char c) {

	sys_write(STDOUT, &c, 1);
}

int strlen(char* str) {
	int size;
	for (size = 0; *str != '\0' ; str++) {
		size++;
	}

	return size;
}

int getchar() {

	static char buffer[2] = {0};

	char read = sys_read(STDOUT, buffer, 1);

	if (read == EOF) {
		return EOF;
	}

	return (int) buffer[0];
}

int scanf(char* c, int length) {

	char read = sys_read(STDOUT, c, length);

	return read;
}

int strcmp(const char* s1, const char* s2) {

	while (*s1 && *s1 == *s2) {
		s1++;
		s2++;
	}

	return *s1 - *s2;
}

char* itoc(int number) {

	int i = 0;
	int j = 0;
	int cnt = 0;

	char* c = malloc(10);

	if (number < 0) {
		number = -number;
		c[i++] = '-';
	}

	while (number >= 10 ) {
		int dig = number % 10;
		number /= 10;
		c[i++] = dig + '0';
		cnt++;
	}
	c[i] = number + '0';

	while (cnt >= j) {
		char aux;
		aux = c[cnt];
		c[cnt--] = c[j];
		c[j++] = aux;
	}

	return c;

}

void clear_screen() {
	sys_clear_screen();
}

void exit() {
	sys_exit();
}