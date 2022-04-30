# Makefile
all: diskimage bootloader make_interrupt library utils shell cat cd cp ls mkdir mv kernel

# Recipes
diskimage:
	dd if=/dev/zero of=out/system.img bs=512 count=2880

bootloader:
	nasm src/asm/bootloader.asm -o out/bootloader
	dd if=out/bootloader of=out/system.img bs=512 count=1 conv=notrunc

kernel:
	bcc -ansi -c -o out/kernel.o src/c/kernel.c
	nasm -f as86 src/asm/kernel.asm -o out/kernel_asm.o
	ld86 -o out/kernel -d out/kernel.o out/kernel_asm.o out/lib_interrupt.o out/std_lib.o out/utils.o out/string.o out/lib_utils.o
	dd if=out/kernel of=out/system.img bs=512 conv=notrunc seek=1

make_interrupt:
	nasm -f as86 src/asm/interrupt.asm -o out/lib_interrupt.o

library:
	bcc -ansi -c -o out/std_lib.o src/c/std_lib.c
	bcc -ansi -c -o out/string.o src/c/string.c
	bcc -ansi -c -o out/program.o src/c/program.c
	bcc -ansi -c -o out/textio.o src/c/textio.c
	bcc -ansi -c -o out/fileio.o src/c/fileio.c

utils:
	bcc -ansi -c -o out/utils.o src/c/utils.c
	nasm -f as86 src/asm/utils.asm -o out/lib_utils.o

shell:
	bcc -ansi -c -o out/shell.o src/c/shell.c
	ld86 -o out/shell -d out/shell.o out/std_lib.o out/string.o out/utils.o out/program.o out/textio.o out/lib_interrupt.o out/lib_utils.o

cat:
	bcc -ansi -c -o out/cat.o src/c/cat.c
	ld86 -o out/cat -d out/cat.o out/textio.o out/fileio.o out/program.o out/utils.o out/string.o out/std_lib.o out/lib_interrupt.o out/lib_utils.o

cd:
	bcc -ansi -c -o out/cd.o src/c/cd.c
	ld86 -o out/cd -d out/cd.o out/textio.o out/fileio.o out/program.o out/string.o out/std_lib.o out/utils.o out/lib_interrupt.o out/lib_utils.o

cp:
	bcc -ansi -c -o out/cp.o src/c/cp.c
	ld86 -o out/cp -d out/cp.o out/textio.o out/fileio.o out/program.o out/string.o out/std_lib.o out/utils.o out/lib_interrupt.o out/lib_utils.o

ls:
	bcc -ansi -c -o out/ls.o src/c/ls.c
	ld86 -o out/ls -d out/ls.o out/textio.o out/fileio.o out/program.o out/string.o out/std_lib.o out/utils.o out/lib_interrupt.o out/lib_utils.o

mkdir:
	bcc -ansi -c -o out/mkdir.o src/c/mkdir.c
	ld86 -o out/mkdir -d out/mkdir.o out/textio.o out/fileio.o out/program.o out/string.o out/std_lib.o out/utils.o out/lib_interrupt.o out/lib_utils.o

mv:
	bcc -ansi -c -o out/mv.o src/c/mv.c
	ld86 -o out/mv -d out/mv.o out/textio.o out/fileio.o out/program.o out/string.o out/std_lib.o out/utils.o out/lib_interrupt.o out/lib_utils.o

file_insert:
	gcc src/tc_lib/tc_gen.c src/tc_lib/tc_lib -o out/tc_gen
	./out/tc_gen

build: all

run:
	bochs -f src/config/if2230.config

build-run: build run