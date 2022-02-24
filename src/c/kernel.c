// Kode kernel
// PENTING : FUNGSI PERTAMA YANG DIDEFINISIKAN ADALAH main(),
//   cek spesifikasi untuk informasi lebih lanjut

// TODO : Tambahkan implementasi kode C

#include "header/kernel.h"

int main() {

	char buf[128];
	clearScreen();
	makeInterrupt21();
	
	readString(buf);
	printString(buf);
	
	while(true);
}

void handleInterrupt21(int AX, int BX, int CX, int DX) {
	switch (AX) {
	    case 0x0:
	      printString(BX);
	      break;
	    case 0x1:
	      readString(BX);
	      break;
	    default:
	      printString("Invalid interrupt");
	}
}

void printString(char *string){}

void readString(char *string){}

void clearScreen() {
	int i = 0;
	int j = 0;
	for (i = 0; i < 80; i++) {
		for (j = 0; j < 25; j++) {
			putInMemory(0xB000, 0x8000 + 50*i + 2*j, 0x20);
			putInMemory(0xB000, 0x8001 + 50*i + 2*j, 0xF);
		}
	}
}

