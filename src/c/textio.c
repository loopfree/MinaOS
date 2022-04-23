#include "header/textio.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

int puts(char *string) {
	// writes a string to stdout up to but not including the null character.
	// A newline character is appended to the output.
	interrupt(0x21, 0x0, string, 0x0, 0x0);
}

char *gets(char *string){
	// reads a line from stdin and stores it into the string 
	// pointed to by str.
	interrupt(0x21, 0x1, string, 0x0, 0x0);
}