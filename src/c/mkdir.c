#include "header/filesystem.h"
#include "header/std_type.h"
#include "header/textio.h"
#include "header/fileio.h"
#include "header/program.h"
#include "header/utils.h"

int main() {
    struct message msg;
    get_message(&msg);
    // msg.arg1

    if (strlen(msg.arg1) == 0) {
        printString("mkdir: Missing operands\n");
        continue;
    }

    strcpy(metadata.node_name, msg.arg1);
    metadata.parent_index = msg.current_directory;
    metadata.filesize = 0;
    write(&metadata, &ret_code);

    if (ret_code == FS_SUCCESS) {
        
    }
    else if (ret_code == FS_W_FILE_ALREADY_EXIST) {
        printString("mkdir: File or directory already exists\n");
    }
    else if (ret_code == FS_W_NOT_ENOUGH_STORAGE) {
        printString("mkdir: Not enough storage\n");
    }
    else if (ret_code == FS_W_MAXIMUM_NODE_ENTRY) {
        printString("mkdir: Maximum node entry\n");
    }
    else if (ret_code == FS_W_MAXIMUM_SECTOR_ENTRY) {
        printString("mkdir: Maximum sector entry\n");
    }
    else if (ret_code == FS_W_INVALID_FOLDER) {
        printString("mkdir: Invalid folder\n");
    }

    exit();
}