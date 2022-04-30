// Tim Asisten Sister 19 - Test case generator milestone 2
// Diedit oleh: kelompok minaOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAMA_IMAGE "out/system.img"

typedef unsigned char byte;

// Link dengan tc_lib
// insert_file & create_folder menerima relative pathing
extern void insert_file(byte buf[2880][512], char *fname, byte parent_idx);
extern void create_folder(byte buf[2880][512], char *fname, byte parent_idx);

int main(int argc, char const *argv[]) {
    // Load entire file and save to buffer
    FILE *image = fopen(NAMA_IMAGE, "rb");

    if (image == NULL) {
        fprintf(stderr, "Error : File image <%s> not found\n", NAMA_IMAGE);
        exit(1);
    }

    byte imagebuffer[2880][512];
    for (int i = 0; i < 2880; i++)
        fread(imagebuffer[i], 512, 1, image);

    // Close file descriptor and overwrite
    fclose(image);
    image = fopen(NAMA_IMAGE, "wb");

    create_folder(imagebuffer, "bin", 0xFF);
    insert_file(imagebuffer, "out/cat", 0x0);
    insert_file(imagebuffer, "out/cd", 0x0);
    insert_file(imagebuffer, "out/cp", 0x0);
    insert_file(imagebuffer, "out/ls", 0x0);
    insert_file(imagebuffer, "out/mkdir", 0x0);
    insert_file(imagebuffer, "out/mv", 0x0);
    insert_file(imagebuffer, "out/shell", 0x0);

    // Overwrite old file
    for (int i = 0; i < 2880; i++)
        fwrite(imagebuffer[i], 512, 1, image);

    fclose(image);
    return 0;
}
