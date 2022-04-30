#include "header/filesystem.h"
#include "header/string.h"
#include "header/textio.h"
#include "header/fileio.h"
#include "header/program.h"
#include "header/utils.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

int main() {
    struct message msg;
	struct node_filesystem node_fs_buffer;
	struct node_entry node;

    int i;
    bool found;
	char path_str[128]; 

    get_message(&msg);
    interrupt(0x21, 0x2, &node_fs_buffer, FS_NODE_SECTOR_NUMBER, 0x1);

    if (strlen(msg.arg2) == 0) {
        puts("cd: Missing operands\n");
    }

    // cd /
    if (strcmp(msg.arg2, "/")) {
        set_cwd(FS_NODE_P_IDX_ROOT);
        clear(path_str, strlen(path_str));
    }

    // cd ..
    else if (strcmp(msg.arg2, "..")){
        if (msg.current_directory == FS_NODE_P_IDX_ROOT) {		// if 'cd ..' from root directory
            puts("cd: Fails to navigate up one directory level because current working dirrectory is root\n");
        } 
        else {
            set_cwd(node_fs_buffer.nodes[msg.current_directory].parent_node_index);
        }
    }

    // cd <folder>
    else {
        found = false;
        for (i=0; i<FS_NODE_SECTOR_CAP && !found; i++) {
            node = node_fs_buffer.nodes[i];
            if (node.parent_node_index == msg.current_directory) {
                if (strcmp(msg.arg2, node.name) && node.sector_entry_index == FS_NODE_S_IDX_FOLDER) {
                    set_cwd(i);
                    found = true;
                }
            }
        }
        if (!found) {
            puts("cd: No such directory\n");
        }
    }

    exit();
}