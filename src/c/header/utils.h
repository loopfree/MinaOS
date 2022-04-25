#ifndef UTILS_H
#define UTILS_H

#include "header/fileio.h"
#include "header/string.h"
#include "header/kernel.h"

#define FS_MESSAGE_SECTOR_NUMBER 0x10A

struct message {
    byte current_directory;
    char arg1[64];
    char arg2[64];
    char arg3[64];
    int next_program_segment;
    byte other[315];    
};

bool set_message(byte current_directory, char* args);
// Menyimpan message ke filesystem sektor berdasarkan cwd dan
// input dari shell

void get_message(struct message* msg);
// Melakukan penyalinan terhadap msg berdasarkan message pada
// filesystem sektor

void set_cwd(byte current_directory);
// Mengupdate message di filesystem sektor sesuai current_directory

#endif
