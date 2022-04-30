#include "header/filesystem.h"
#include "header/textio.h"
#include "header/fileio.h"
#include "header/program.h"
#include "header/utils.h"
#include "header/string.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

int main() {
    struct message msg;
	struct node_filesystem node_fs_buffer;
	struct node_entry node;
	byte temp_dir;
    
    int i , j;
    bool found;
    char filerename[64];
    char argsdir[8][64];

    get_message(&msg);
    interrupt(0x21, 0x2, &node_fs_buffer, FS_NODE_SECTOR_NUMBER, 0x1);

    if (strlen(msg.arg2) == 0 || strlen(msg.arg3) == 0) {
        puts("mv: Missing operands");
    }

    temp_dir = msg.current_directory;
    strsplit(argsdir, msg.arg3, '/'); 

    // mv <src> /<dst>
    if (msg.arg3[0] == '/') {
        temp_dir = FS_NODE_P_IDX_ROOT;
        strcpy(filerename, argsdir[0]);
        if (strcmp(argsdir[0], "..")) {
            puts("mv: Invalid path");
        }
    }

    // mv <src> ../<dst>
    else if (strlen(argsdir[1]) != 0) {
        if (strcmp(argsdir[0], "..")) {
            temp_dir = node_fs_buffer.nodes[temp_dir].parent_node_index;
            strcpy(filerename, argsdir[1]);
        }
        else {
            puts("mv: Invalid path");
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
            strcpy(filerename, msg.arg2);
        }
        // 'dest' is a file
        else {
            puts("mv: Target is a file and already exists");
        }
    }

    // find src
    found = false;
    for (i = 0; i < FS_NODE_SECTOR_CAP && !found; i++) {
        node = node_fs_buffer.nodes[i];
        if (node.parent_node_index == msg.current_directory && strcmp(msg.arg2, node.name)) {
            j = i;
            found = true;
        }
    }

    if (!found) {
        puts("mv: No such file or directory");
    }
    else {
        node_fs_buffer.nodes[j].parent_node_index = temp_dir;
        strcpy(node_fs_buffer.nodes[j].name, filerename);
        interrupt(0x21, 0x3, &node_fs_buffer, FS_NODE_SECTOR_NUMBER, 0x2);
    }

    exit();
}