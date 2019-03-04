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
bootloader.img: ./boot/bootloader.asm
	nasm -f bin -o ./boot/bootloader.img ./boot/bootloader.asm
	
loadkernel.img: ./boot/loadkernel.asm
	nasm -f bin -o ./boot/loadkernel.img ./boot/loadkernel.asm
	
###########################32��Ʈ Ŀ�� ����###########################	
init32.o: ./init/init32.c
	gcc -c -masm=intel -m32 -ffreestanding ./init/init32.c -o ./init/init32.o

page.o: ./kernel/x86/page.c
	gcc -c -masm=intel -m32 -ffreestanding ./kernel/x86/page.c -o ./kernel/x86/page.o

syscheck.o: ./kernel/x86/syscheck.c
	gcc -c -masm=intel -m32 -ffreestanding ./kernel/x86/syscheck.c -o ./kernel/x86/syscheck.o
	
stdkernel.o: ./lib/x86/stdkernel.c
	gcc -c -masm=intel -m32 -ffreestanding ./lib/x86/stdkernel.c -o ./lib/stdkernel.o
	
###########################64��Ʈ Ŀ�� ����###########################	
init64.o: ./init/init64.c
	gcc -c -masm=intel -m64 -ffreestanding ./init/init64.c -o ./init/init64.o
	
stdkernel64.o: ./lib/stdkernel.c
	gcc -c -masm=intel -m64 -ffreestanding ./lib/stdkernel.c -o ./lib/stdkernel.o
	
idt.o: ./kernel/idt.c
	gcc -c -masm=intel -m64 -ffreestanding ./kernel/idt.c -o ./kernel/idt.o
	
keyboard.o: ./drivers/keyboard.c
	gcc -c -masm=intel -m64 -ffreestanding ./drivers/keyboard.c -o ./drivers/keyboard.o
	
###########################Ŀ�� �̹��� ����###########################
Kernel32N.img: 
	ld -T ./elf_i386.x -nostdlib ./init/init32.o ./kernel/x86/page.o ./kernel/x86/syscheck.o ./lib/x86/stdkernel.o -o ./Kernel32N.img
	
Kernel32.img: ./Kernel32N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel32N.img ./Kernel32.img

Kernel64N.img: 
	ld -T ./elf_x86_64.x -nostdlib ./init/init64.o ./lib/stdkernel.o ./kernel/idt.o -o ./Kernel64N.img
	
Kernel64.img: ./Kernel64N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel64N.img ./Kernel64.img
	
###########################�ü�� �̹��� ����###########################	
Disk.img: ./boot/bootloader.img ./boot/loadkernel.img ./Kernel32.img ./Kernel64.img
	cat ./boot/bootloader.img ./boot/loadkernel.img ./Kernel32.img ./Kernel64.img > Disk.img
	
clean:
	rm -rf ./boot/bootloader.img ./boot/loadkernel.img 
	rm -rf ./init/init32.o ./kernel/x86/page.o ./kernel/x86/syscheck.o ./lib/stdkernel.o
	rm -rf ./init/init64.o ./lib/stdkernel.o ./kernel/idt.o ./drivers/keyboard.o
