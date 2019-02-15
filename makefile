#############################################
#			Infinite Synthesis x64	  		#
#											#
# ���� ��: makefile							#
# ����: Infinite Synthesis ���� �� makefile	#
# ���� �ۼ�: 2019-01-22						#
#############################################
#		���� �����̽��ٷ� �Է����� �� ��.		#
#############################################

all: bootloader.img loadkernel.img init32.o page.o stdkernel.o syscheck.o Kernel32N.img Kernel32.img Disk.img clean

###########################��Ʈ�δ� ����###########################
bootloader.img: ./Bootloader/bootloader.asm
	nasm -f bin -o ./Bootloader/bootloader.img ./Bootloader/bootloader.asm
	
loadkernel.img: ./Bootloader/loadkernel.asm
	nasm -f bin -o ./Bootloader/loadkernel.img ./Bootloader/loadkernel.asm
	
###########################32��Ʈ Ŀ�� ����###########################	
init32.o: ./Kernel32/init32.c
	gcc -c -masm=intel -m32 -ffreestanding ./Kernel32/init32.c -o ./Kernel32/init32.o

page.o: ./Kernel32/page.c
	gcc -c -masm=intel -m32 -ffreestanding ./Kernel32/page.c -o ./Kernel32/page.o

syscheck.o: ./Kernel32/syscheck.c
	gcc -c -masm=intel -m32 -ffreestanding ./Kernel32/syscheck.c -o ./Kernel32/syscheck.o
	
stdkernel.o: ./Kernel32/stdkernel.c
	gcc -c -masm=intel -m32 -ffreestanding ./Kernel32/stdkernel.c -o ./Kernel32/stdkernel.o

###########################Ŀ�� �̹��� ����###########################
Kernel32N.img: 
	ld -T ./elf_i386.x -nostdlib ./Kernel32/init32.o ./Kernel32/page.o ./Kernel32/syscheck.o ./Kernel32/stdkernel.o -o ./Kernel32/Kernel32N.img
	
Kernel32.img: ./Kernel32/Kernel32N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel32/Kernel32N.img ./Kernel32/Kernel32.img
	
###########################�ü�� �̹��� ����###########################	
Disk.img: ./Bootloader/bootloader.img ./Bootloader/loadkernel.img ./Kernel32/Kernel32.img 
	cat ./Bootloader/bootloader.img ./Bootloader/loadkernel.img ./Kernel32/Kernel32.img > Disk.img
	
clean:
	rm -rf ./Bootloader/bootloader.img ./Bootloader/loadkernel.img 
	rm -rf ./Kernel32/page.o ./Kernel32/init32.o ./Kernel32/stdkernel.o ./Kernel32/memcheck.o
	rm -rf ./Kernel32/Kernel32.img ./Kernel32/Kernel32/Kernel32N.img
