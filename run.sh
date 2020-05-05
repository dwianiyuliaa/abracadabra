echo bootloader
nasm bootloader.asm -o bootloader
dd if=bootloader of=system.img bs=512 count=1 conv=notrunc

echo filesystem
dd if=map.img of=system.img bs=512 count=1 seek=256 conv=notrunc
dd if=dir.img of=system.img bs=512 count=2 seek=257 conv=notrunc
dd if=sectors.img of=system.img bs=512 count=1 seek=259 conv=notrunc

echo compiling:

echo - text
bcc -ansi -c -o text.o lib/text/text.c

echo - file
bcc -ansi -c -o file.o lib/file/file.c

echo - folder
bcc -ansi -c -o folder.o lib/folder/folder.c

echo - mat
bcc -ansi -c -o mat.o lib/mat/mat.c

echo - kernel
bcc -ansi -c -o kernel.o kernel.c
nasm -f as86 kernel.asm -o kernel_asm.o

echo linking + loading
ld86 -o kernel -d kernel.o file.o folder.o mat.o text.o kernel_asm.o
dd if=kernel of=system.img bs=512 conv=notrunc seek=1

echo shell
bcc -ansi -c -o shell.o shell.c
nasm -f as86 kernel.asm -o kernel_asm.o
ld86 -o shell -d shell.o kernel_asm.o

echo load file
gcc loadFile.c -o loadFile
./loadFile shell

echo run
bochs -f if2230.config