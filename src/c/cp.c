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

    if (strlen(msg.arg2) == 0 || strlen(msg.arg3) == 0) {
        puts("cp: Missing operands\n");
    }

    metadata.parent_index = msg.current_directory;
    strcpy(metadata.node_name, msg.arg2);

    // read(&metadata, &ret_code);
    interrupt(0x4, &metadata, &ret_code, 0x0, 0x0);

    if (ret_code == FS_SUCCESS) {
        strcpy(metadata.node_name, msg.arg3);
        // write(&metadata, &ret_code);
        interrupt(0x5, &metadata, &ret_code, 0x0, 0x0);

        if (ret_code == FS_SUCCESS) {
        }
        else if (ret_code == FS_W_FILE_ALREADY_EXIST) {
            puts("cp: File already exists\n");
        }
        else if (ret_code == FS_W_NOT_ENOUGH_STORAGE) {
            puts("cp: Not enough storage\n");
        }
        else if (ret_code == FS_W_MAXIMUM_NODE_ENTRY) {
            puts("cp: Maximum node entry\n");
        }
        else if (ret_code == FS_W_MAXIMUM_SECTOR_ENTRY) {
            puts("cp: Maximum sector entry\n");
        }
        else if (ret_code == FS_W_INVALID_FOLDER) {
            puts("cp: Invalid folder\n");
        }

    }
    else if (ret_code == FS_R_NODE_NOT_FOUND) {
        puts("cp: No such file or directory\n");
    }
    else if (ret_code == FS_R_TYPE_IS_FOLDER) {
        puts("cp: Cannot copy directory\n");
    }

    exit(msg.next_program_segment);
}