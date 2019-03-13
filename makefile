#############################################
#			Infinite Synthesis x64	  		#
#											#
# ���� ��: makefile							#
# ����: Infinite Synthesis ���� �� makefile	#
# ���� �ۼ�: 2019-01-22						#
#############################################
#		���� �����̽��ٷ� �Է����� �� ��.		#
#############################################

CC32=gcc -m32
CC64=gcc -m64
CFLAGS=-c -masm=intel -ffreestanding
INCLUDE32=./include/x86
INCLUDE64=./include
NASM=nasm -f bin


all: bootloader.img loadkernel.img init32.o page.o stdkernel.o syscheck.o init64.o stdkernel64.o idt.o keyboard.o shell.o Kernel32N.img Kernel32.img Kernel64N.img Kernel64.img Disk.img clean

###########################��Ʈ�δ� ����###########################
bootloader.img: ./boot/bootloader.asm
	$(NASM) ./boot/bootloader.asm -o ./boot/bootloader.img
	
loadkernel.img: ./boot/loadkernel.asm
	$(NASM) ./boot/loadkernel.asm -o ./boot/loadkernel.img 
	
###########################32��Ʈ Ŀ�� ����###########################	
init32.o: ./init/init32.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./init/$@

page.o: ./kernel/x86/page.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./kernel/x86/$@

syscheck.o: ./kernel/x86/syscheck.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./kernel/x86/$@
	
stdkernel.o: ./lib/x86/stdkernel.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./lib/x86/$@
	
###########################64��Ʈ Ŀ�� ����###########################	
init64.o: ./init/init64.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./init/$@
	
stdkernel64.o: ./lib/stdkernel.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./lib/$@
	
idt.o: ./kernel/idt.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./kernel/$@
	
keyboard.o: ./drivers/keyboard.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./drivers/$@
	
shell.o: ./kernel/shell/shell.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./kernel/shell/$@
	
###########################Ŀ�� �̹��� ����###########################
Kernel32N.img: 
	ld -T ./elf_i386.x -nostdlib ./init/init32.o ./kernel/x86/page.o ./kernel/x86/syscheck.o ./lib/x86/stdkernel.o -o ./Kernel32N.img
	
Kernel32.img: ./Kernel32N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel32N.img ./Kernel32.img

Kernel64N.img: 
	ld -T ./elf_x86_64.x -nostdlib ./init/init64.o ./lib/stdkernel64.o ./kernel/idt.o ./kernel/shell/shell.o ./drivers/keyboard.o -o ./Kernel64N.img
	
Kernel64.img: ./Kernel64N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel64N.img ./Kernel64.img
	
###########################�ü�� �̹��� ����###########################	
Disk.img: ./boot/bootloader.img ./boot/loadkernel.img ./Kernel32.img ./Kernel64.img
	cat ./boot/bootloader.img ./boot/loadkernel.img ./Kernel32.img ./Kernel64.img > Disk.img
	
clean:
	rm -rf ./boot/*.img
	rm -rf ./Kernel32.img ./Kernel32N.img ./Kernel64.img ./Kernel64N.img
	find ./ -name '*.o' -exec rm {} \;
