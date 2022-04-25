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

void clear(byte *ptr, unsigned int n) {
	int i;
	for (i = 0; i < n; i++)
		ptr[i] = 0;
}
