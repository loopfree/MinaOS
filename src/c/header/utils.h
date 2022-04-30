#ifndef UTILS_H
#define UTILS_H

#include "filesystem.h"
#include "std_lib.h"
#include "string.h"

#define FS_MESSAGE_SECTOR_NUMBER 0x10A

struct message {
    byte current_directory;
    char arg1[64];
    char arg2[64];
    char arg3[64];
    int next_program_segment;
    byte other[315];    
};

extern int getCurrentSegment();

void set_message(byte current_directory, char* args, bool init);
// Menyimpan message ke filesystem sektor berdasarkan cwd dan
// input dari shell

void get_message(struct message* msg);
// Melakukan penyalinan terhadap msg berdasarkan message pada
// filesystem sektor

void reload_message();
// Melakukan reload terhadap message pada filesystem sektor
// yaitu mengganti arg dan next_program_segment berdasarkan 
// byte* other

void set_cwd(byte current_directory);
// Mengupdate message di filesystem sektor sesuai current_directory

#endif
