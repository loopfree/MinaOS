#ifndef STD_LIB_H
#define STD_LIB_H

#include "std_type.h"

// Operator matematika umum
int div(int a, int b);
int mod(int a, int n);

// Operasi standar bahasa C

void memcpy(byte *dest, byte *src, unsigned int n);
// Mengcopy n bytes yang ditunjuk src ke dest

bool abs(int* number);
// megnubah nilai number menjadi positif
// mengembalikan keadaan awal number (- / +)

void clear(byte *ptr, unsigned int n);
// Mengosongkan byte array yang memiliki panjang n

#endif
