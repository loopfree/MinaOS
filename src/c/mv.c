#include "header/filesystem.h"
#include "header/std_type.h"
#include "header/textio.h"
#include "header/fileio.h"
#include "header/program.h"
#include "header/utils.h"

int main() {
    struct message msg;
    struct file_metadata metadata;
    enum fs_retcode ret_code;
	struct node_filesystem node_fs_buffer;
	struct node_entry node;
	byte current_dir = FS_NODE_P_IDX_ROOT;
	byte temp_dir;
    
    int i , j;
    bool found;
    char filerename[64];
    char argsdir[8][64];

    get_message(&msg);

    if (strlen(msg.arg1) == 0 || strlen(msg.arg2) == 0) {
        printString("mv: Missing operands\n");
    }

    temp_dir = current_dir;
    strsplit(argsdir, msg.arg2, '/'); 

    // mv <src> /<dst>
    if (msg.arg2[0] == '/') {
        temp_dir = FS_NODE_P_IDX_ROOT;
        strcpy(filerename, argsdir[0]);
        if (strcmp(argsdir[0], "..")) {
            printString("mv: Invalid path\n");
        }
    }

    // mv <src> ../<dst>
    else if (strlen(argsdir[1]) != 0) {
        if (strcmp(argsdir[0], "..")) {
            temp_dir = node_fs_buffer.nodes[temp_dir].parent_node_index;
            strcpy(filerename, argsdir[1]);
        }
        else {
            printString("mv: Invalid path\n");
        }
    }

    // mv <src> <dst>
    else {
        strcpy(filerename, argsdir[0]);
    }

    // find dest
    found = false;
    for (i = 0; i < FS_NODE_SECTOR_CAP && !found; i++) {
        node = node_fs_buffer.nodes[i];
        if (node.parent_node_index == temp_dir && strcmp(node.name, filerename)) {
            j = i;
            found = true;
        }
    }
    if (found) {
        // 'dest' is a folder
        if (node.sector_entry_index == FS_NODE_S_IDX_FOLDER) {
            temp_dir = j;
            strcpy(filerename, msg.arg1);
        }
        // 'dest' is a file
        else {
            printString("mv: Target is a file and already exists\n");
        }
    }

    // find src
    found = false;
    for (i = 0; i < FS_NODE_SECTOR_CAP && !found; i++) {
        node = node_fs_buffer.nodes[i];
        if (node.parent_node_index == current_dir && strcmp(msg.arg1, node.name)) {
            j = i;
            found = true;
        }
    }

    if (!found) {
        printString("mv: No such file or directory");
    }
    else {
        node_fs_buffer.nodes[j].parent_node_index = temp_dir;
        strcpy(node_fs_buffer.nodes[j].name, filerename);
        writeSector(&node_fs_buffer, FS_NODE_SECTOR_NUMBER, 0x2);
    }

    exit(msg.next_program_segment);
}