#include "header/utils.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

void set_message(byte current_directory, char* args, bool init) {
    struct message msg;
    int argc, argmc;
    char temp[8][256];
    char argsmini[8][64];
    int i;

    // mem clear
    clear(&msg, sizeof(struct message));
    for (i = 0; i < 8; i++) {
        clear(&temp, 256);
        clear(&argsmini, 64);
    }

    msg.current_directory = current_directory;
    argc = strsplit(temp, args, ';');

    if (argc == 0) {    // no more commands
        msg.next_program_segment = 0x2000;
        return;
    }

    if (init)
        msg.next_program_segment = 0x3000;
    else
        msg.next_program_segment += 0x1000;

    // Config args
    argmc = strsplit(argsmini, temp[0], ' ');
    if (argmc >= 1) {
        strcpy(&msg.arg1, argsmini[0]);
    if (argmc >= 2) {
        strcpy(&msg.arg2, argsmini[1]);
    }
    if (argmc >= 3) {
        strcpy(&msg.arg3, argsmini[2]);
    }

    for (i = 1; i < argc; i++) {
        strcat(&msg.other, &msg.other, args[i]);
    }

    // writeSector(&msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    interrupt(0x21, 0x3, &msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
}

void get_message(struct message* msg) {
    clear(msg, sizeof(struct message));
    // readSector(msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    interrupt(0x21, 0x2, msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
}

void reload_message() {
    struct message msg;
    clear(&msg, sizeof(struct message));
    // readSector(msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    interrupt(0x21, 0x2, &msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    set_message(msg.current_directory, msg.other);
}

void set_cwd(byte current_directory) {
    struct message msg;
    // readSector(&msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    interrupt(0x21, 0x2, &msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    msg.current_directory = current_directory;
    // writeSector(&msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    interrupt(0x21, 0x3, &msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
}