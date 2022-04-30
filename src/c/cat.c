#include "header/filesystem.h"
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
        puts("cat: Missing operands\n");
    }

    strcpy(metadata.node_name, msg.arg2);
    metadata.parent_index = msg.current_directory;

    read(&metadata, &ret_code);

    if (ret_code == FS_SUCCESS) { // file exist
        puts(metadata.buffer);
        puts("\n");
    }
    else if (ret_code == FS_R_NODE_NOT_FOUND) {
        puts("cat: No such file or directory\n");
    }
    else if (ret_code == FS_R_TYPE_IS_FOLDER) {
        puts("cat: Target is a directory\n");
    }

    exit();
}