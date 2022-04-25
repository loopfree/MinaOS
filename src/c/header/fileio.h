#ifndef FILEIO_H
#define FILEIO_H

#include "filesystem.h"
#include "std_lib.h"

//  read
void read(struct file_metadata *metadata, enum fs_retcode *return_code);

//  write
void write(struct file_metadata *metadata, enum fs_retcode *return_code);

#endif