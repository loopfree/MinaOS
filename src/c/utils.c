#include "header/utils.h"

bool set_message(byte current_directory, char* args) {
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

    argc = strsplit(temp, args, ';');

    if (argc == 0) {
        return false;
    }

    msg.current_directory = current_directory;

    argmc = strsplit(argsmini, temp[0], ' ');

    // Config next program segment
    if (argc > 1) {
        msg.next_program_segment = program_segment(argsmini[0]);
        if (msg.next_program_segment == 0x0) {
            return false;
        }
    }
    else {
        msg.next_program_segment = 0x2000;
    }

    // Config args
    if (argmc >= 1) {
        strcpy(&msg.arg1, argsmini[1]);
    }
    if (argmc >= 2) {
        strcpy(&msg.arg2, argsmini[2]);
    }
    if (argmc >= 3) {
        strcpy(&msg.arg3, argsmini[3]);
    }

    for (i = 1; i < argc; i++) {
        strcat(&msg.other, &msg.other, args[i]);
    }

    writeSector(&msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    return true;
}

void get_message(struct message* msg) {
    struct message new_msg;
    clear(msg, sizeof(struct message));
    readSector(msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    memcpy(&new_msg, msg, sizeof(struct message));
    set_message(new_msg.current_directory, new_msg.other);
}

void set_cwd(byte current_directory) {
    struct message msg;
    readSector(&msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    msg.current_directory = current_directory;
    writeSector(&msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
}

int program_segment(char* command) {
    if (strcmp(command, "cd")) {
        return 0x3000;
    }
    else if (strcmp(command, "ls")) {
        return 0x4000;
    }
    else if (strcmp(command, "mv")) {
        return 0x5000;
    }
    else if (strcmp(command, "mkdir")) {
        return 0x6000;
    }
    else if (strcmp(command, "cat")) {
        return 0x7000;
    }
    else if (strcmp(command, "cp")) {
        return 0x8000;
    }
    else {
        return 0x0;
    }
}
