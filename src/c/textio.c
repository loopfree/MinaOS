extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

int puts(char *string) {
  interrupt(0x21, ..., ..., ..., ...);
  // . . .
}
