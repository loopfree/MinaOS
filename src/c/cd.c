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

    int i;
    bool found;
	char path_str[128]; 

    get_message(&msg);

    if (strlen(msg.arg1) == 0) {
        printString("cd: Missing operands\n");
    }

    // cd /
    if (strcmp(msg.arg1, "/")) {
        current_dir = FS_NODE_P_IDX_ROOT;
        clear(path_str, strlen(path_str));
    }

    // cd ..
    else if (strcmp(msg.arg1, "..")){
        if (current_dir == FS_NODE_P_IDX_ROOT) {		// if 'cd ..' from root directory
            printString("cd: Fails to navigate up one directory level because current working dirrectory is root\n");
        } 
        else {
            current_dir = node_fs_buffer.nodes[current_dir].parent_node_index;
        }
    }

    // cd <folder>
    else {
        found = false;
        for (i=0; i<FS_NODE_SECTOR_CAP && !found; i++) {
            node = node_fs_buffer.nodes[i];
            if (node.parent_node_index == current_dir) {
                if (strcmp(msg.arg1, node.name) && node.sector_entry_index == FS_NODE_S_IDX_FOLDER) {
                    current_dir = i;
                    found = true;
                }
            }
        }
        if (!found) {
            printString("cd: No such directory\n");
        }
    }

    exit(msg.next_program_segment);
}