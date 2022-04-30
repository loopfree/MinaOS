#include "header/filesystem.h"
#include "header/std_type.h"
#include "header/textio.h"
#include "header/fileio.h"
#include "header/program.h"
#include "header/utils.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

int main() {
    struct message msg;
    struct file_metadata metadata;
    enum fs_retcode ret_code;
    get_message(&msg);

    if (strlen(msg.arg2) == 0) {
        puts("mkdir: Missing operands\n");
    }

    strcpy(metadata.node_name, msg.arg2);
    metadata.parent_index = msg.current_directory;
    metadata.filesize = 0;
    write(&metadata, &ret_code);

    if (ret_code == FS_SUCCESS) {
        
    }
    else if (ret_code == FS_W_FILE_ALREADY_EXIST) {
        puts("mkdir: File or directory already exists\n");
    }
    else if (ret_code == FS_W_NOT_ENOUGH_STORAGE) {
        puts("mkdir: Not enough storage\n");
    }
    else if (ret_code == FS_W_MAXIMUM_NODE_ENTRY) {
        puts("mkdir: Maximum node entry\n");
    }
    else if (ret_code == FS_W_MAXIMUM_SECTOR_ENTRY) {
        puts("mkdir: Maximum sector entry\n");
    }
    else if (ret_code == FS_W_INVALID_FOLDER) {
        puts("mkdir: Invalid folder\n");
    }

    exit();
}