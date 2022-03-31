#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__

#include "std_type.h"

#define FS_<Filesystem>_SECTOR_NUMBER   // Menunjukkan lokasi sektor filesystem.
#define FS_NODE_P_IDX_ROOT              // Isi byte P node yang terletak pada root.
#define FS_NODE_S_IDX_FOLDER            // Isi byte S node yang merupakan folder.



// Digunakan untuk merepresentasikan filesystem pada kode.
struct map_filesystem;
struct node_filesystem;
struct sector_filesystem;

// Digunakan untuk merepresentasikan entri setiap filesystem terkait.
struct node_entry;
struct sector_entry;

// Menyimpan informasi terkait file untuk keperluan operasi read atau write.
struct file_metadata;

// Sebagai return code untuk operasi filesystem sistem operasi.
enum fs_retcode;

struct file_metadata {
    byte* buffer;
    char* node_name;
    byte parent_index;
    unsigned int filesize;
};

#endif