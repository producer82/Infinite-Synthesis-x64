#############################################
#			Infinite Synthesis x64	  		#
#											#
# ���� ��: makefile							#
# ����: Infinite Synthesis ���� �� makefile	#
# ���� �ۼ�: 2019-01-22						#
#############################################
#		���� �����̽��ٷ� �Է����� �� ��.		#
#############################################

all: bootloader.img loadkernel.img init32.o page.o stdkernel.o syscheck.o init64.o stdkernel64.o idt.o Kernel32N.img Kernel32.img Kernel64N.img Kernel64.img Disk.img clean

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
	
###########################64��Ʈ Ŀ�� ����###########################	
init64.o: ./Kernel64/init64.c
	gcc -c -masm=intel -m64 -ffreestanding ./Kernel64/init64.c -o ./Kernel64/init64.o
	
stdkernel64.o: ./Kernel64/stdkernel.c
	gcc -c -masm=intel -m64 -ffreestanding ./Kernel64/stdkernel.c -o ./Kernel64/stdkernel.o
	
idt.o: ./Kernel64/idt.c
	gcc -c -masm=intel -m64 -ffreestanding ./Kernel64/idt.c -o ./Kernel64/idt.o
	
###########################Ŀ�� �̹��� ����###########################
Kernel32N.img: 
	ld -T ./elf_i386.x -nostdlib ./Kernel32/init32.o ./Kernel32/page.o ./Kernel32/syscheck.o ./Kernel32/stdkernel.o -o ./Kernel32/Kernel32N.img
	
Kernel32.img: ./Kernel32/Kernel32N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel32/Kernel32N.img ./Kernel32/Kernel32.img

Kernel64N.img: 
	ld -T ./elf_x86_64.x -nostdlib ./Kernel64/init64.o ./Kernel64/stdkernel.o ./Kernel64/idt.o -o ./Kernel64/Kernel64N.img
	
Kernel64.img: ./Kernel64/Kernel64N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel64/Kernel64N.img ./Kernel64/Kernel64.img
	
###########################�ü�� �̹��� ����###########################	
Disk.img: ./Bootloader/bootloader.img ./Bootloader/loadkernel.img ./Kernel32/Kernel32.img 
	cat ./Bootloader/bootloader.img ./Bootloader/loadkernel.img ./Kernel32/Kernel32.img ./Kernel64/Kernel64.img > Disk.img
	
clean:
	rm -rf ./Bootloader/bootloader.img ./Bootloader/loadkernel.img 
	rm -rf ./Kernel32/page.o ./Kernel32/init32.o ./Kernel32/stdkernel.o ./Kernel32/memcheck.o
