// Kode kernel
// PENTING : FUNGSI PERTAMA YANG DIDEFINISIKAN ADALAH main(),

#include "header/kernel.h"
#include "header/filesystem.h"

int main() {
	clearScreen();
	fillMap();
	makeInterrupt21();
	shell();
}

void handleInterrupt21(int AX, int BX, int CX, int DX) {
	switch (AX) {
	    case 0x0:
	    	printString(BX);
	    	break;
	    case 0x1:
	    	readString(BX);
	    	break;
	    case 0x2:
	    	readSector(BX, CX, 0x1);
	    	break;
	   	case 0x3:
	   		writeSector(BX, CX, 0x1);
	   		break;
	   	case 0x4:
	   		read(BX, CX);
	   		break;
	   	case 0x5:
	   		write(BX, CX);
	   		break;
	    default:
	    	printString("Invalid interrupt\n");
	}
}

void printString(char *string){
	int i = 0;
	while (string[i] != 0x0) {
		if (string[i] != 0xA) { // bukan enter
			interrupt(0x10, 0xE00 + string[i], 0, 0, 0);
		}
		else { // enter
			interrupt(0x10, 0xE0D, 0, 0, 0);
			interrupt(0x10, 0xE0A, 0, 0, 0);
		}
		i += 1;
	}
}

/*
void printInt(int n) {
	char str[64];
	clear(str, 64);
	inttostr(n, str);
	printString(str);
}
*/

void readString(char *string)
{
	int i=0;
	char input = 0;

	while(1)
	{
		input = interrupt(0x16, 0, 0, 0, 0);

		// input enter
		if (input == 0xd)
		{
			break;
		}

		// input backspace
		if (input == 0x8)
		{
			// kalau input backspace tidak di awal
			if (i != 0)
			{
				i -= 1;
				string[i] = 0x0;
				interrupt(0x10, 0x0e00 + input, 0, 0, 0);
				interrupt(0x10, 0x0e00 + string[i], 0, 0, 0);
				i -= 1;
				interrupt(0x10, 0x0e00 + input, 0, 0, 0);
				i += 1;
			}
			// else
			// Kalau input backspace diawal (i=0) abaikan saja
		}

		// input another ascii
		else
		{
			string[i] = input;
			interrupt(0x10, 0x0e00 + input, 0, 0, 0);
			i += 1;
		}
	}

	string[i] = 0x0;
	string[i+1] = 0xa;

	interrupt(0x10, 0xe0a, 0, 0, 0);
	interrupt(0x10, 0xe0d, 0, 0, 0);

	return;
}

void clearScreen() {
	int i = 0;
	for (i = 0; i < 5000; i++) {
		putInMemory(0xB000, 0x8000 + 2*i, 0x20);
		putInMemory(0xB000, 0x8001 + 2*i, 0xF);
	}
	interrupt(0x10, 0x200, 0x0, 0x0, 0x0);
}

void readSector(byte *buffer, int sector_number, int sector_read_count) {
    //int sector_read_count = 0x01;
    int cylinder, sector;
    int head, drive;

    cylinder = div(sector_number, 36) << 8; // CH
    sector   = mod(sector_number, 18) + 1;  // CL

    head  = mod(div(sector_number, 18), 2) << 8; // DH
    drive = 0x00;                                // DL

    interrupt(
        0x13,                       // Interrupt number
        0x0200 | sector_read_count, // AX
        buffer,                     // BX
        cylinder | sector,          // CX
        head | drive                // DX
    );
}

void writeSector (byte *buffer, int sector_number, int sector_read_count) {
    //int sector_read_count = 0x01;
    int cylinder, sector;
    int head, drive;

    cylinder = div(sector_number, 36) << 8; // CH
    sector   = mod(sector_number, 18) + 1;  // CL

    head  = mod(div(sector_number, 18), 2) << 8; // DH
    drive = 0x00;                                // DL

    interrupt(
        0x13,                       // Interrupt number
        0x0300 | sector_read_count, // AX
        buffer,                     // BX
        cylinder | sector,          // CX
        head | drive                // DX
    );
}

void fillMap() {
	struct map_filesystem map_fs_buffer;
	int i;

	// Load filesystem map
	readSector(&map_fs_buffer, FS_MAP_SECTOR_NUMBER, 0x1);

	for (i = 0; i < 16; i++) {
		map_fs_buffer.is_filled[i] = true;
	}

	for (i = 256; i < 512; i++) {
		map_fs_buffer.is_filled[i] = true;
	}

	// Update filesystem map
	writeSector(&map_fs_buffer, FS_MAP_SECTOR_NUMBER, 0x1);
}


void read(struct file_metadata *metadata, enum fs_retcode *return_code) {
	struct node_filesystem   node_fs_buffer;
	struct sector_filesystem sector_fs_buffer;
	// Tambahkan tipe data yang dibutuhkan
	struct sector_entry sector;
	bool foundNode = false;
	byte parent;
	byte sector_idx;
	int foundindex = 0;
	int i = 0;
	char buf[8192];

	clear(buf, 8192);

	// Memasukkan filesystem dari storage ke memori buffer
	readSector(&node_fs_buffer , FS_NODE_SECTOR_NUMBER , 0x2);

	// 1. Cari node dengan nama dan lokasi yang sama pada filesystem.
	for(i = 0 ; i < FS_NODE_SECTOR_CAP ; i++){
		parent = node_fs_buffer.nodes[i].parent_node_index;
		if( (parent == metadata->parent_index) && 
			(strcmp(node_fs_buffer.nodes[i].name, metadata->node_name) )){
			foundNode = true;
			foundindex = i;
			break;
		}
	}
	if(!foundNode){
		// tidak ditemukan node yang cocok
		*return_code = FS_R_NODE_NOT_FOUND;
		return;
	} // ditemukan node yang cocok
	
	// 2. Cek tipe node yang ditemukan
	sector_idx = node_fs_buffer.nodes[foundindex].sector_entry_index;
	if(sector_idx == FS_NODE_S_IDX_FOLDER){
		// tipe node adalah folder
		*return_code = FS_R_TYPE_IS_FOLDER;
		return;
	}

	// Pembacaan

	// 0. Memasukkan isi sector filesystem dari storage ke memory
	readSector(&sector_fs_buffer , FS_SECTOR_SECTOR_NUMBER , 0x1);
	// 1. memcpy() entry sector sesuai dengan byte S
	memcpy( &sector, &(sector_fs_buffer.sector_list[sector_idx]), 16);
	// 2. Lakukan iterasi proses berikut, i = 0..15
	// 3. Baca byte entry sector untuk mendapatkan sector number partisi file
	// 4. Jika byte bernilai 0, selesaikan iterasi
	// 5. Jika byte valid, lakukan readSector()
	//    dan masukkan kedalam buffer yang disediakan pada metadata
	// 6. Lompat ke iterasi selanjutnya hingga iterasi selesai
	i = 0;
	metadata->buffer = buf;
	while (i < 16 && sector.sector_numbers[i] != 0x0){
		readSector(metadata->buffer+i*512, sector.sector_numbers[i], 0x1);
		i++;
	}
	
	// 7. Tulis retcode FS_SUCCESS dan ganti filesize pada akhir proses pembacaan.
	*return_code = FS_SUCCESS;
	metadata->filesize = i * 512;
	return;
}


void write(struct file_metadata *metadata, enum fs_retcode *return_code) {
	struct node_filesystem   node_fs_buffer;
	struct sector_filesystem sector_fs_buffer;
	struct map_filesystem    map_fs_buffer;
	int nodeIdx, sectorIdx;
	bool found, finished;
	int i, j;
	int availableSector = 0;
	byte buffer[16];

	clear(buffer, 16);

	// Masukkan filesystem dari storage ke memori
	readSector(&node_fs_buffer, FS_NODE_SECTOR_NUMBER, 0x2);
	readSector(&sector_fs_buffer, FS_SECTOR_SECTOR_NUMBER, 0x1);
	readSector(&map_fs_buffer, FS_MAP_SECTOR_NUMBER, 0x1);

	// 1. Cari node dengan nama dan lokasi parent yang sama pada node.
	for (i = 0; i < FS_NODE_SECTOR_CAP; i++) {
		if (strcmp(node_fs_buffer.nodes[i].name, metadata->node_name) 
			&& node_fs_buffer.nodes[i].parent_node_index == metadata->parent_index) {
			*return_code = FS_W_FILE_ALREADY_EXIST;
			return;
		}
	}
	
	// 2. Cari entri kosong pada filesystem node dan simpan indeks.
	found = false;
	for (i = 0; i < FS_NODE_SECTOR_CAP && !found; i++) {
		if (strlen(node_fs_buffer.nodes[i].name) == 0) {
			nodeIdx = i;
			found = true;
		}	
	}
	if (!found) {
		*return_code = FS_W_MAXIMUM_NODE_ENTRY;
		return;
	}
	
	// 3. Cek dan pastikan entry node pada indeks P adalah folder.
	if (metadata->parent_index != FS_NODE_P_IDX_ROOT) {
		if (node_fs_buffer.nodes[metadata->parent_index].sector_entry_index != FS_NODE_S_IDX_FOLDER) {
			*return_code = FS_W_INVALID_FOLDER;
			return;
		}
	}

	// 4. Cek dan pastikan sisa storage cukup untuk filesize dari metadata.
	for (i = 0; i < FS_MAP_SECTOR_CAP; i++) {
		if (!map_fs_buffer.is_filled[i])
			availableSector += 1;
	}
	if (metadata->filesize > availableSector * 512) {
		*return_code = FS_W_NOT_ENOUGH_STORAGE;
		return;
	}

	// 5. Cek pada filesystem sector apakah terdapat entry yang masih kosong.
	found = false;
	for (i = 0; i < FS_SECTOR_SECTOR_CAP && !found; i++) {
		if (sector_fs_buffer.sector_list[i].sector_numbers[0] == 0x0) {
			sectorIdx = i;
			found = true;
		}
	}
	if (!found) {
		*return_code = FS_W_MAXIMUM_SECTOR_ENTRY;
		return;
	}

	// Penulisan
	// 1. Tuliskan metadata nama dan byte P ke node pada memori buffer
	strcpy(node_fs_buffer.nodes[nodeIdx].name, metadata->node_name);
	node_fs_buffer.nodes[nodeIdx].parent_node_index = metadata->parent_index;

	// 2. Jika menulis folder, tuliskan byte S dengan nilai 
	//    FS_NODE_S_IDX_FOLDER dan lompat ke langkah ke-8
	//    Asumsi: filesize of folder = 0
	if (metadata->filesize == 0) {
		node_fs_buffer.nodes[nodeIdx].sector_entry_index = FS_NODE_S_IDX_FOLDER;
	}
	else {
		// 3. Jika menulis file, tuliskan juga byte S sesuai indeks sector
		node_fs_buffer.nodes[nodeIdx].sector_entry_index = sectorIdx;
		// 4. Persiapkan variabel j = 0 untuk iterator entry sector yang kosong
		j = 0;
		// 5. Persiapkan variabel buffer untuk entry sector kosong
		clear(buffer, 16);
		
		// 6. Lakukan iterasi berikut dengan kondisi perulangan 
		// 		(penulisan belum selesai && i = 0..255)
		//    1. Cek apakah map[i] telah terisi atau tidak
		//    2. Jika terisi, lanjutkan ke iterasi selanjutnya / continue
		//    3. Tandai map[i] terisi
		//    4. Ubah byte ke-j buffer entri sector dengan i
		//    5. Tambah nilai j dengan 1
		//    6. Lakukan writeSector() dengan file pointer buffer pada metadata 
		//       dan sektor tujuan i
		//    7. Jika ukuran file yang telah tertulis lebih besar atau sama dengan
		//       filesize pada metadata, penulisan selesai
		finished = false;
		for (i = 0; i < 255 && !finished; i++) {
			if (map_fs_buffer.is_filled[i])
				continue;
			
			map_fs_buffer.is_filled[i] = true;
			buffer[j] = i;
			j += 1;
			writeSector(metadata->buffer, i, 1);

			if (j * 512 >= metadata->filesize)
				finished = true;
		}
		
		// 7. Lakukan update dengan memcpy() buffer entri sector dengan 
		//    buffer filesystem sector
		memcpy(sector_fs_buffer.sector_list[sectorIdx].sector_numbers, buffer, 16);
	}

	// 8. Lakukan penulisan seluruh filesystem (map, node, sector) ke storage
	//    menggunakan writeSector() pada sektor yang sesuai
	writeSector(&map_fs_buffer, FS_MAP_SECTOR_NUMBER, 1);
	writeSector(&node_fs_buffer, FS_NODE_SECTOR_NUMBER, 2);
	writeSector(&sector_fs_buffer, FS_SECTOR_SECTOR_NUMBER, 1);

	// 9. Kembalikan retcode FS_SUCCESS
	*return_code = FS_SUCCESS;
}

void shell() {
	int i, j, n;
	char input_buf[64];	
	char path_str[128]; 
	char args[8][64]; 
	char argsdir[8][64];
	char filerename[64];
	struct sector_filesystem sector_fs_buffer;
	struct sector_entry sector;
	
	enum fs_retcode ret_code;
	struct node_filesystem node_fs_buffer;
	struct node_entry node;
	struct file_metadata metadata;
	byte current_dir = FS_NODE_P_IDX_ROOT;
	bool found;
	byte folder, temp_dir;
	
	clear(path_str, 128);
	
	while (true) {
		clear(input_buf, 64);
		clear(filerename, 64);
		clear(&metadata, 16);
		for (i = 0; i < 8; i++) clear(args[i], 64);
		for (i = 0; i < 8; i++) clear(argsdir[i], 64);
	
		readSector(&node_fs_buffer, FS_NODE_SECTOR_NUMBER, 0x2);

		printString("minaOS@IF2230:");
		printCWD(path_str, current_dir);				// print path to cwd
		printString(path_str);							// print path
		printString("$ ");
		readString(input_buf);							// input command
		strsplit(args, input_buf, ' ');

		if (strlen(args[0]) == 0) {
			continue;
		}

		// cd: Change Directory
		if (strcmp(args[0], "cd")) {
			if (strlen(args[1]) == 0) {
				printString("cd: Missing operands\n");
				continue;
			}

			// cd /
			if (strcmp(args[1], "/")) {
				current_dir = FS_NODE_P_IDX_ROOT;
				clear(path_str, strlen(path_str));
			}

			// cd ..
			else if (strcmp(args[1], "..")){
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
						if (strcmp(args[1], node.name) && node.sector_entry_index == FS_NODE_S_IDX_FOLDER) {
							current_dir = i;
							found = true;
						}
					}
				}
				if (!found) {
					printString("cd: No such directory\n");
				}
			}
		}

		// ls: List
		else if (strcmp(args[0], "ls")) {
			// ls 
			if (strlen(args[1]) == 0) {
				for (i=0; i<FS_NODE_SECTOR_CAP; i++) {
					node = node_fs_buffer.nodes[i];
					if (node.parent_node_index == current_dir && strlen(node.name) != 0) {
						printString(node.name);
						printString("\n");
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
						if (strcmp(args[1], node.name)) {
							folder = i;
							found = true;
						}
					}
				}
				if (!found) {
					printString("ls: No such file or directory\n");
				}
				// Melakukan ls terhadap folder
				else {
					for (i=0; i<FS_NODE_SECTOR_CAP; i++) {
						node = node_fs_buffer.nodes[i];
						if (node.parent_node_index == folder && strlen(node.name) != 0) {
							printString(node.name);
							printString("\n");
						}
					}
				}
			}
		}

		// mv: Move
		// mv <src> <dst>
		else if (strcmp(args[0], "mv")) {
			if (strlen(args[1]) == 0 || strlen(args[2]) == 0) {
				printString("mv: Missing operands\n");
				continue;
			}

			temp_dir = current_dir;
			strsplit(argsdir, args[2], '/'); 

			// mv <src> /<dst>
			if (args[2][0] == '/') {
				temp_dir = FS_NODE_P_IDX_ROOT;
				strcpy(filerename, argsdir[0]);
				if (strcmp(argsdir[0], "..")) {
					printString("mv: Invalid path\n");
					continue;
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
					continue;
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
					strcpy(filerename, args[1]);
				}
				// 'dest' is a file
				else {
					printString("mv: Target is a file and already exists\n");
					continue;
				}
			}

			// find src
			found = false;
			for (i = 0; i < FS_NODE_SECTOR_CAP && !found; i++) {
				node = node_fs_buffer.nodes[i];
				if (node.parent_node_index == current_dir && strcmp(args[1], node.name)) {
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
		}

		// mkdir: Make Directory
		// mkdir <folder>
		else if (strcmp(args[0], "mkdir")) {
			if (strlen(args[1]) == 0) {
				printString("mkdir: Missing operands\n");
				continue;
			}

			strcpy(metadata.node_name, args[1]);
			metadata.parent_index = current_dir;
			metadata.filesize = 0;
			write(&metadata, &ret_code);

			if (ret_code == FS_SUCCESS) {
				
			}
			else if (ret_code == FS_W_FILE_ALREADY_EXIST) {
				printString("mkdir: File or directory already exists\n");
			}
			else if (ret_code == FS_W_NOT_ENOUGH_STORAGE) {
				printString("mkdir: Not enough storage\n");
			}
			else if (ret_code == FS_W_MAXIMUM_NODE_ENTRY) {
				printString("mkdir: Maximum node entry\n");
			}
			else if (ret_code == FS_W_MAXIMUM_SECTOR_ENTRY) {
				printString("mkdir: Maximum sector entry\n");
			}
			else if (ret_code == FS_W_INVALID_FOLDER) {
				printString("mkdir: Invalid folder\n");
			}
		}

		// cat: Concatenate
		// cat <file>
		else if (strcmp(args[0], "cat")) {
			if (strlen(args[1]) == 0) {
				printString("cat: Missing operands\n");
				continue;
			}

			strcpy(metadata.node_name, args[1]);
			metadata.parent_index = current_dir;

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
		}

		// cp: Copy
		// cp <file_1> <file_2>
		else if (strcmp(args[0], "cp")) {
			if (strlen(args[1]) == 0 || strlen(args[2]) == 0) {
				printString("cp: Missing operands\n");
			}

			metadata.parent_index = current_dir;
			strcpy(metadata.node_name, args[1]);

			read(&metadata, &ret_code);
			if (ret_code == FS_SUCCESS) {
				strcpy(metadata.node_name, args[2]);
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
		}

		else {
			printString(args[0]);
			printString(": Unknown command\n");
		}
	}
}

void printCWD(char* path, byte cwd) {
	struct node_filesystem node_fs_buffer;
	struct node_entry node;
	byte temp_dir = cwd;

	clear(path, 128);
	readSector(&node_fs_buffer, FS_NODE_SECTOR_NUMBER, 2);

	while (temp_dir != FS_NODE_P_IDX_ROOT) {
		node = node_fs_buffer.nodes[temp_dir];
		temp_dir = node.parent_node_index;
		strcat(path, node.name, path);
		strcat(path, "/", path);
	}

	strcat(path, "~", path);
}