#ifndef _FILEIO_H
#define _FILEIO_H

#include "filesystem.h"

void read(struct file_metadata *metadata, enum fs_retcode *return_code);
void write(struct file_metadata *metadata, enum fs_retcode *return_code);

#endif
