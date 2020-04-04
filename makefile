#############################################
#			Infinite Synthesis x64	  		#
#											#
# 파일 명: makefile							#
# 설명: Infinite Synthesis 빌드 용 makefile	#
# 최초 작성: 2019-01-22						#
#############################################
#			탭을 스페이스바로 입력하지 말 것.		#
#############################################

CC32=gcc -m32
CC64=gcc -m64
CFLAGS=-c -masm=intel -ffreestanding
INCLUDE32=./include/x86
INCLUDE64=./include
NASM=nasm -f bin


all: bootloader init32.o page.o stdkernel.o syscheck.o init64.o gdt.o stdkernel64.o idt.o keyboard.o shell.o sh_routine.o Kernel32N.img Kernel32.img Kernel64N.img Kernel64.img Disk.img clean

###########################부트로더 빌드###########################
bootloader: ./boot/makefile
	cd boot; $(MAKE)
	
############################커널 빌드###########################	
kernel: ./kernel/makefile
	cd kernel; $(MAKE)
	

###########################커널 이미지 빌드###########################
Kernel32N.img: 
	ld -T ./elf_i386.x -nostdlib ./kernel/init/init32.o ./kernel/x86/page.o ./kernel/x86/syscheck.o ./lib/x86/stdkernel.o -o ./Kernel32N.img
	
Kernel32.img: ./Kernel32N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel32N.img ./Kernel32.img

Kernel64N.img: 
	ld -T ./elf_x86_64.x -nostdlib ./kernel/init/init64.o ./lib/stdkernel64.o ./kernel/idt.o ./kernel/gdt.o ./kernel/shell/shell.o ./kernel/drivers/keyboard.o ./kernel/shell/sh_routine.o -o ./Kernel64N.img
	
Kernel64.img: ./Kernel64N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel64N.img ./Kernel64.img
	
###########################운영체제 이미지 빌드###########################	
Disk.img: ./boot/boot.bin ./Kernel32.img ./Kernel64.img
	cat ./boot/boot.bin ./Kernel32.img ./Kernel64.img > Disk.img
	
clean:
	find ./ -name '*.o' -exec rm {} \;
