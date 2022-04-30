#include "header/program.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

void exec(struct file_metadata* meta, int segment) {
    char buf[20];
    // meng-eksekusi file pada segment tertentu
    interrupt(0x21, 0x1, buf, 0x0, 0x0);
    // setelah mengeksekusi
    interrupt(0x21, 0x6, meta, segment, 0x0);

}

// Kalau ada ./ cari di cwd (run di lokal)
// Kalau tidak ada ./ di bin 0x00
void exit() {
    // keluar dari program dan reload
    struct file_metadata meta;
    enum fs_retcode return_code;
    struct message msg;
    char buffer[20];

    clear(&meta, sizeof(struct file_metadata));
    clear(&msg, sizeof(struct message));

    get_message(&msg);

    // ada ./
    // misalnya: ./execute_smth
    if (msg.arg1[0] == '.' && msg.arg1[1] == '/') {
        meta.parent_index = msg.current_directory; //cwd
    }
    // tidak ada ./
    // misalnya: execute_smth
    else {
        meta.parent_index = 0x00; //bin
    }

    if (msg.next_program_segment == 0x2000) {
        meta.node_name = "shell";
        meta.parent_index = 0x00;
    }
    else {
        meta.node_name = buffer;
        strcpy(meta.node_name, msg.arg1);
    }

    exec(&meta, msg.next_program_segment);
}