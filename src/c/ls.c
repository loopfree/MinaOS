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
    byte folder, temp_dir;
    
    int i;
    bool found;

    get_message(&msg);

    // ls 
    if (strlen(msg.arg1) == 0) {
        for (i=0; i<FS_NODE_SECTOR_CAP; i++) {
            node = node_fs_buffer.nodes[i];
            if (node.parent_node_index == current_dir && strlen(node.name) != 0) {
                puts(node.name);
                puts("\n");
            }
        }
    }

    // ls <folder>
    else {
        // Mencari folder
        found = false;
        for (i=0; i<FS_NODE_SECTOR_CAP && !found; i++) {
            node = node_fs_buffer.nodes[i];
            if (node.parent_node_index == current_dir) {
                if (strcmp(msg.arg1, node.name)) {
                    folder = i;
                    found = true;
                }
            }
        }
        if (!found) {
            puts("ls: No such file or directory\n");
        }
        // Melakukan ls terhadap folder
        else {
            for (i=0; i<FS_NODE_SECTOR_CAP; i++) {
                node = node_fs_buffer.nodes[i];
                if (node.parent_node_index == folder && strlen(node.name) != 0) {
                    puts(node.name);
                    puts("\n");
                }
            }
        }
    }

    exit(msg.next_program_segment);
}