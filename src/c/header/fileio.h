#ifndef FILEIO_H
#define FILEIO_H

#include "filesystem.h"
#include "std_lib.h"

void read(struct file_metadata *metadata, enum fs_retcode *return_code);
void write(struct file_metadata *metadata, enum fs_retcode *return_code);

#endif