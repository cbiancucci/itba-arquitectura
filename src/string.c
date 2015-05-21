#include "../include/string.h"

int strcmp(char * s1, char * s2) {
	int i;
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	if (len1 != len2)
		return len1 - len2;
	for (i = 0; i < len1; i++)
		if (s1[i] != s2[i])
			return s1[i] > s2[i] ? 1 : -1;
	return 0;
}

int strlen(char * s) {
	int i = 0;
	while (s[i])
		i++;
	return i;
}
