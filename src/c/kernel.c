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

void printString(char *string){
	int i = 0; 
	int l = strlen(string);
	while(1){
	  for(i = 0; i < l; i++){
	     interrupt(0x10,0xE*256+chars[i],0,0,0);
	  }
	}
}

void readString(char *string)
{
	int i=0;
	char input = 0;

	while(1)
	{
		input = interrupt(0x16, 0, 0, 0, 0);

		// input enter
		if (input == 0xd)
		{
			break;
		}

		// input backspace
		if (input == 0x8)
		{
			// kalau input backspace tidak di awal
			if (i!=0)
			{
				i -= 1;
				string[i] = 0x0;
				interrupt(0x10, 0x0e * 256 + input, 0, 0, 0);
				interrupt(0x10, 0x0e * 256 + string[i], 0, 0, 0);
				i -= 1;
				interrupt(0x10, 0x0e * 256 + input, 0, 0, 0);
				i += 1;
			}
			// else
			// Kalau input backspace diawal (i=0) abaikan saja
		}

		// input another ascii
		else
		{
			string[i] = input;
			interrupt(0x10, 0x0e * 256 + input, 0, 0, 0);
			i += 1;
		}
	}

	string[i] = 0x0;
	string[i+1] = 0xa;

	// enter biar rapih
	string[i+2] = 0xd;

	return;
}

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

