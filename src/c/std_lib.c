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
	else
		return false;
}

bool strcmpn(char *s1, char *s2, unsigned int startIdx, unsigned int endIdx) {
	if (strlen(s1) >= endIdx && strlen(s2) >= endIdx) {
		for (int i=0; i < endIdx; i++) {
			if (s1[startIdx] != s2[i]) 
				return false;
			startIdx += 1;
		}
		return true;
	}
	else 
		return false;
}

void strsplit(char dst[][64], char *src, char splitter) {
	int j = 0;
	int k = 0;
	bool readingsplitter = true;
	for (int i = 0; i < strlen(src); i++) {
		if (src[i] == splitter) {
			if (readingsplitter)
				continue;
			else {
				j += 1;
				k = 0;
			}
		}
		else {
			dst[j][k] = src[i];
			k += 1;
            readingsplitter = false;
		}
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
