#include "header/program.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

void exec(struct file_metadata* meta, int segment) {
    // meng-eksekusi file pada CX(0x2000) segment
    interrupt(0x21, 0x6, meta, segment, 0x0);
}

void exit() {
    // keluar dari program dan reload
    struct file_metadata meta;
    enum fs_retcode return_code;
    struct message msg;

    clear(&meta, sizeof(struct file_metadata));
    clear(&msg, sizeof(struct message));

    get_message(&msg);

    if (msg.next_program_segment == 0x2000) {
        meta.node_name = "shell";
        meta.parent_index = 0x00;
    }
    else {
        strcpy(meta.node_name, prog_name);

        // update parent index
    }

    exec(&meta, prog_seg);
}