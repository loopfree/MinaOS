#include "header/std_lib.h"
#include "header/string.h"
#include "header/filesystem.h"
#include "header/utils.h"
#include "header/program.h"

extern int interrupt(int int_number, int AX, int BX, int CX, int DX);

int main() {
    char input_buf[512];
	char path_str[128];
    struct message msg;

	clear(input_buf, 512);
	clear(path_str, 128);
	clear(&msg, sizeof(struct message));

	get_message(&msg);

	puts("minaOS@IF2230:");
	printCWD(path_str, msg.current_directory);		// print path to cwd
	puts(path_str);									// print path
	puts("$ ");
	gets(input_buf);								// input command

	set_message(FS_NODE_P_IDX_ROOT, input_buf, true);
    exit();
}

void printCWD(char* path, byte cwd) {
	struct node_filesystem node_fs_buffer;
	struct node_entry node;
	byte temp_dir = cwd;

	clear(path, 128);
	interrupt(0x2, &node_fs_buffer, FS_MAP_SECTOR_NUMBER, 0x2, 0x0);

	while (temp_dir != FS_NODE_P_IDX_ROOT) {
		node = node_fs_buffer.nodes[temp_dir];
		temp_dir = node.parent_node_index;
		strcat(path, node.name, path);
		strcat(path, "/", path);
	}

	strcat(path, "~", path);
}