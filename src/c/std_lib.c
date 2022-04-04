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
	int i;
	for (i = 0; i < n ; i++) {
		dest[i] = src[i];
	}
}

unsigned int strlen(char *string) {
	unsigned int i = 0;
	while (string[i] != '\0')
		i += 1;
	return i;
}

// void swap(char *x, char *y){
//     char t;
// 	t = *x;
// 	*x = *y;
// 	*y = t;
// }

// char* reverse(char *buffer, int i, int j){
//     while (i < j){
//         swap(&buffer[i++], &buffer[j--]);
//     }
//     return buffer;
// }

bool abs(int* number){
	bool neg = false;
	if (*number < 0){
		neg = true;
		*number *= -1;
	}else{
		// do nothing
	}
	return neg;
}

#define INTCAP 64

void inttostr(int src , char* s){
	int number = src;
	int digit , lastDigitIdx ,i;
	bool isNegative;
	char digits[INTCAP];
	i = INTCAP - 1;

	isNegative = abs(&number);

	while(number != 0){
		digit = mod(number, 10);
		digits[i] = digit + 48;		// 48 ..57 in ASCII : 0..9
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

bool strcmpn(char *s1, char *s2, unsigned int startIdx, unsigned int endIdx) {
	if (strlen(s1) >= endIdx && strlen(s2) >= endIdx) {
		int i;
		for (i=0; i < endIdx; i++) {
			if (s1[startIdx] != s2[i]) 
				return false;
			startIdx += 1;
		}
		return true;
	}
	else 
		return false;
}

int strsplit(char dst[][64], char *src, char splitter) {
	int i;
	int j = 0;
	int k = 0;
	bool readingsplitter = true;
	for (i = 0; i < strlen(src); i++) {
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
	return j;
}

void strcpy(char *dst, char *src) {
	int i;
	for (i = 0; i <= strlen(src); i++) 
		dst[i] = src[i];
}

void clear(byte *ptr, unsigned int n) {
	int i;
	for (i = 0; i < n; i++)
		ptr[i] = 0;
}

void strcat(char* dst, char* src1, char* src2) {
	int i = 0;
	int j = 0;
	char str1[128];
	char str2[128];

	clear(str1, 128);
	clear(str2, 128);
	
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

