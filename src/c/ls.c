#include "header/filesystem.h"
#include "header/textio.h"
#include "header/fileio.h"
#include "header/program.h"
#include "header/utils.h"

int main() {
    struct message msg;
	struct node_filesystem node_fs_buffer;
	struct node_entry node;
    byte folder, temp_dir;
    
    int i;
    bool found;

    get_message(&msg);
    interrupt(0x21, 0x2, &node_fs_buffer, FS_NODE_SECTOR_NUMBER, 0x1);

    // ls 
    if (strlen(msg.arg1) == 0) {
        for (i=0; i<FS_NODE_SECTOR_CAP; i++) {
            node = node_fs_buffer.nodes[i];
            if (node.parent_node_index == msg.current_directory && strlen(node.name) != 0) {
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
            if (node.parent_node_index == msg.current_directory) {
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

    exit();
}