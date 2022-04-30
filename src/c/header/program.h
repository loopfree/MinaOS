#ifndef PROGRAM_H
#define PROGRAM_H

#include "filesystem.h"
#include "std_type.h"
#include "std_lib.h"
#include "string.h"
#include "fileio.h"
#include "utils.h"

void exec(struct file_metadata* meta, int segment);
void exit();

#endif
