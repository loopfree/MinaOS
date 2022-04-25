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
        printString("cat: Missing operands\n");
        continue;
    }

    strcpy(metadata.node_name, msg.arg1);
    metadata.parent_index = msg.current_directory;

    read(&metadata, &ret_code);
    if (ret_code == FS_SUCCESS) { // file exist
        printString(metadata.buffer);
        printString("\n");
    }
    else if (ret_code == FS_R_NODE_NOT_FOUND) {
        printString("cat: No such file or directory\n");
    }
    else if (ret_code == FS_R_TYPE_IS_FOLDER) {
        printString("cat: Target is a directory\n");
    }

    exit();
}