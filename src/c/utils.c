#include "header/utils.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

void set_message(byte current_dir, char* args) {
    struct message msg;
    clear(&msg, sizeof(struct message));
    msg.current_directory = current_dir;
    msg.next_program_segment = 0x2000;
    strcpy(msg.other, args);
    interrupt(0x21, 0x3, &msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
}

void reload_message() {
    struct message msg;
    int argc, argmc;
    char temp[8][256];
    char argsmini[8][256];
    char args[315];
    int i;
    byte temp_dir;
    bool segfault = false;

    clear(args, 315);

    // store currdir
    get_message(&msg);
    temp_dir = msg.current_directory;
    strcpy(args, msg.other);

    // mem clear
    clear(&msg, sizeof(struct message));
    for (i = 0; i < 8; i++) {
        clear(temp[i], 256);
        clear(argsmini[i], 256);
    }

    msg.current_directory = temp_dir;

    argc = strsplit(temp, args, ';');
    
    if (argc == 0) {    // no more commands
        strcpy(msg.arg1, "");
        strcpy(msg.arg2, "");
        strcpy(msg.arg3, "");
        msg.next_program_segment = 0x2000;
    }
    else {
        if (getCurrentSegment() == 0x7000) {
            segfault = true;
        }
        else {
            msg.next_program_segment = getCurrentSegment() + 0x1000;
        }

        if (segfault) {
            strcpy(msg.arg1, "");
            strcpy(msg.arg2, "");
            strcpy(msg.arg3, "");
            msg.next_program_segment = 0x2000;
            interrupt(0x21, 0x0, "Going back to shell because memory segment overflow\n", 0x0, 0x0);
        }
        else {
            // Config args
            argmc = strsplit(argsmini, temp[0], ' ');
            strcpy(msg.arg1, argsmini[0]);
            strcpy(msg.arg2, argsmini[1]);
            strcpy(msg.arg3, argsmini[2]);

            for (i = 1; i < argc; i++) {
                strcat(msg.other, msg.other, temp[i]);
                strcat(msg.other, msg.other, ";");
            }
        }
    }

    interrupt(0x21, 0x3, &msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
}

void get_message(struct message* msg) {
    clear(msg, sizeof(struct message));
    interrupt(0x21, 0x2, msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
}

void set_cwd(byte current_directory) {
    struct message msg;
    clear(&msg, sizeof(struct message));
    interrupt(0x21, 0x2, &msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
    msg.current_directory = current_directory;
    interrupt(0x21, 0x3, &msg, FS_MESSAGE_SECTOR_NUMBER, 0x1);
}