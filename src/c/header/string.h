#ifndef STRING_H
#define STRING_H

#include "std_type.h"

// Operasi standar bahasa C

unsigned int strlen(char *string);
// Mengembalikan panjang suatu null terminated string

void itoa(int src , char* s);
// Mengubah integer menjadi string

bool strcmp(char *s1, char *s2);
// Mengembalikan true jika string sama

int strsplit(char dst[][256], char *src, char splitter);
// Melakukan pemisahan string src berdasarkan splitter dengan maksimum panjang
// partisi adalah 64 karakter, kemudian mengembalikan jumlah string yang displit

void strcpy(char *dst, char *src);
// Melakukan penyalinan null terminated string

void strcat(char* dst, char* src1, char* src2);
// Menggabungkan src1 dan src2 ke dst

#endif
