// Kernel header

#include "std_type.h"
#include "std_lib.h"

// Fungsi bawaan
extern void putInMemory(int segment, int address, char character);
extern int interrupt(int int_number, int AX, int BX, int CX, int DX);
void makeInterrupt21();
void handleInterrupt21(int AX, int BX, int CX, int DX);
void fillMap();

void printString(char *string);
void readString(char *string);
void clearScreen();

void writeSector(byte *buffer, int sector_number, int sector_read_count);
void readSector(byte *buffer, int sector_number, int sector_read_count);

void shell();

void printCWD(char* path, byte cwd);

extern void launchProgram(int segment);
void executeProgram(struct file_metadata *metadata, int segment);