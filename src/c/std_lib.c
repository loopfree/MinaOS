#include "header/std_lib.h"

// Operator matematika umum

int div(int a, int b) {
	return a/b;
}

int mod(int a, int n) {
	return a - div(a,n) * n;
}

// Operasi standar bahasa C

void memcpy(byte *dest, byte *src, unsigned int n) {
	for (int i = 0; i < n ; i++) {
		dest[i] = src[i];
	}
}

unsigned int strlen(char *string) {
	unsigned int i = 0;
	while (string[i] != '\0')
		i += 1;
	return i;
}

bool strcmp(char *s1, char *s2) {
	if (strlen(s1) == strlen(s2)) {
		for (int i = 0; i < strlen(s1); i++) {
			if (s1[i] != s2[i])
				return false;
		}
		return true;
	}
	else {
		return false;
	}
}

void strcpy(char *dst, char *src) {
	for (int i = 0; i <= strlen(src); i++) 
		dst[i] = src[i];
}

void clear(byte *ptr, unsigned int n) {
	for (int i = 0; i < n; i++)
		ptr[i] = 0;
}
