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

    if (strlen(msg.arg1) == 0 || strlen(msg.arg2) == 0) {
        printString("cp: Missing operands\n");
    }

    metadata.parent_index = msg.current_directory;
    strcpy(metadata.node_name, msg.arg1);

    read(&metadata, &ret_code);
    if (ret_code == FS_SUCCESS) {
        strcpy(metadata.node_name, msg.arg2);
        write(&metadata, &ret_code);

        if (ret_code == FS_SUCCESS) {

        }
        else if (ret_code == FS_W_FILE_ALREADY_EXIST) {
            printString("cp: File already exists\n");
        }
        else if (ret_code == FS_W_NOT_ENOUGH_STORAGE) {
            printString("cp: Not enough storage\n");
        }
        else if (ret_code == FS_W_MAXIMUM_NODE_ENTRY) {
            printString("cp: Maximum node entry\n");
        }
        else if (ret_code == FS_W_MAXIMUM_SECTOR_ENTRY) {
            printString("cp: Maximum sector entry\n");
        }
        else if (ret_code == FS_W_INVALID_FOLDER) {
            printString("cp: Invalid folder\n");
        }

    }
    else if (ret_code == FS_R_NODE_NOT_FOUND) {
        printString("cp: No such file or directory\n");
    }
    else if (ret_code == FS_R_TYPE_IS_FOLDER) {
        printString("cp: Cannot copy directory\n");
    }

    exit();
}