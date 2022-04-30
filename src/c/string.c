#include "header/string.h"

unsigned int strlen(char *string) {
	unsigned int i = 0;
	while (string[i] != '\0')
		i += 1;
	return i;
}

void itoa(int src , char* s){
	int number = src;
	int digit , lastDigitIdx ,i;
	bool isNegative;
	char digits[64];
	i = 64 - 1;

	isNegative = abs(&number);

	while(number != 0){
		digit = mod(number, 10);
		digits[i] = digit + 48;
		i--;
		number = div(number, 10);
	}
	if(isNegative){
		digits[i] = '-';
	}

	strcpy(s , digits);
}


bool strcmp(char *s1, char *s2) {
	int i;
	if (strlen(s1) == strlen(s2)) {
		for (i = 0; i < strlen(s1); i++) {
			if (s1[i] != s2[i])
				return false;
		}
		return true;
	}
	else
		return false;
}

int strsplit(char dst[][256], char *src, char splitter) {
	int i;
	int j = 0;
	int k = 0;
	bool readingsplitter = true;
	for (i = 0; i < strlen(src); i++) {
		if (src[i] == splitter) {
			readingsplitter = true;
		}
		else {
			if (readingsplitter) {
				j += 1;
				k = 0;
			}
			dst[j-1][k] = src[i];
			k += 1;
            readingsplitter = false;
		}
	}
	return j;
}

void strcpy(char *dst, char *src) {
	int i;
	for (i = 0; i <= strlen(src); i++) 
		dst[i] = src[i];
}

void strcat(char* dst, char* src1, char* src2) {
	int i = 0;
	int j = 0;
	char str1[1024];
	char str2[1024];

	clear(str1, 1024);
	clear(str2, 1024);
	
	strcpy(str1, src1);
	strcpy(str2, src2);

	while (str1[i] != '\0') {
		dst[j] = str1[i];
		i += 1;
		j += 1;
	}

	i = 0;
	while (str2[i] != '\0') {
		dst[j] = str2[i];
		i += 1;
		j += 1;
	}
}
