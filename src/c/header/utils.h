#include "header/fileio.h"

struct message {
    byte current_directory;
    char arg1[64];
    char arg2[64];
    char arg3[64];
    int next_program_segment; // Dapat digunakan untuk bagian 3.5
    byte other[317];
};

extern int getCurrentSegment();