#include "header/program.h"


extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

void exec(char* filename, CX) {
    // meng-eksekusi file pada CX(0x2000) segment
    interrupt(0x21, 0x6, filename, CX, 0x0);
}

void exit() {
    // keluar dari program dan reload
    struct file_metadata meta;
    meta.node_name    = "shell";
    meta.parent_index = 0x00;

    exec(meta, 0x2000);
}