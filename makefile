#############################################
#			Infinite Synthesis x64	  		#
#											#
# 파일 명: makefile							#
# 설명: Infinite Synthesis 빌드 용 makefile	#
# 최초 작성: 2019-01-22						#
#############################################
#		탭을 스페이스바로 입력하지 말 것.		#
#############################################

CC32=gcc -m32
CC64=gcc -m64
CFLAGS=-c -masm=intel -ffreestanding
INCLUDE32=./include/x86
INCLUDE64=./include
NASM=nasm -f bin


all: bootloader.img loadkernel.img init32.o page.o stdkernel.o syscheck.o init64.o gdt.o stdkernel64.o idt.o keyboard.o shell.o sh_routine.o Kernel32N.img Kernel32.img Kernel64N.img Kernel64.img Disk.img clean

###########################부트로더 빌드###########################
bootloader.img: ./boot/bootloader.asm
	$(NASM) ./boot/bootloader.asm -o ./boot/bootloader.img
	
loadkernel.img: ./boot/loadkernel.asm
	$(NASM) ./boot/loadkernel.asm -o ./boot/loadkernel.img 
	
###########################32비트 커널 빌드###########################	
init32.o: ./init/init32.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./init/$@

page.o: ./kernel/x86/page.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./kernel/x86/$@

syscheck.o: ./kernel/x86/syscheck.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./kernel/x86/$@
	
stdkernel.o: ./lib/x86/stdkernel.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./lib/x86/$@
	
###########################64비트 커널 빌드###########################	
init64.o: ./init/init64.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./init/$@
	
stdkernel64.o: ./lib/stdkernel.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./lib/$@
	
idt.o: ./kernel/idt.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./kernel/$@
	
gdt.o: ./kernel/gdt.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./kernel/$@
	
### 드라이버 빌드
keyboard.o: ./drivers/keyboard.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./drivers/$@
	
### 셸 빌드
shell.o: ./kernel/shell/shell.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./kernel/shell/$@
	
sh_routine.o: ./kernel/shell/sh_routine.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o ./kernel/shell/$@
	
###########################커널 이미지 빌드###########################
Kernel32N.img: 
	ld -T ./elf_i386.x -nostdlib ./init/init32.o ./kernel/x86/page.o ./kernel/x86/syscheck.o ./lib/x86/stdkernel.o -o ./Kernel32N.img
	
Kernel32.img: ./Kernel32N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel32N.img ./Kernel32.img

Kernel64N.img: 
	ld -T ./elf_x86_64.x -nostdlib ./init/init64.o ./lib/stdkernel64.o ./kernel/idt.o ./kernel/gdt.o ./kernel/shell/shell.o ./drivers/keyboard.o ./kernel/shell/sh_routine.o -o ./Kernel64N.img
	
Kernel64.img: ./Kernel64N.img
	objcopy -O binary -S -j .text -j .bss -j .data -j .rodata ./Kernel64N.img ./Kernel64.img
	
###########################운영체제 이미지 빌드###########################	
Disk.img: ./boot/bootloader.img ./boot/loadkernel.img ./Kernel32.img ./Kernel64.img
	cat ./boot/bootloader.img ./boot/loadkernel.img ./Kernel32.img ./Kernel64.img > Disk.img
	
clean:
	rm -rf ./boot/*.img
	rm -rf ./Kernel32.img ./Kernel32N.img ./Kernel64.img ./Kernel64N.img
	find ./ -name '*.o' -exec rm {} \;
