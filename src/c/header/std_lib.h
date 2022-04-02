#include "std_type.h"

// Operator matematika umum
int div(int a, int b);
int mod(int a, int n);

// Operasi standar bahasa C

void memcpy(byte *dest, byte *src, unsigned int n);
// Mengcopy n bytes yang ditunjuk src ke dest

unsigned int strlen(char *string);
// Mengembalikan panjang suatu null terminated string

bool strcmp(char *s1, char *s2);
// Mengembalikan true jika string sama

bool strcmpn(char *s1, char *s2, unsigned int startIdx, unsigned int endIdx);
// Mengembalikan true jika substring dari s1 dari startIdx (inclusive) hingga
// endIdx (exclusive) adalah s2

int strsplit(char dst[][64], char *src, char splitter);
// Melakukan pemisahan string src berdasarkan splitter dengan maksimum panjang
// partisi adalah 64 karakter, kemudian mengembalikan jumlah string yang displit

void strcpy(char *dst, char *src);
// Melakukan penyalinan null terminated string

void clear(byte *ptr, unsigned int n);
// Mengosongkan byte array yang memiliki panjang n

void concat(char* merge, char* str1, char* str2)
// Menggabungkan str1 dan str2 menjadi merge
