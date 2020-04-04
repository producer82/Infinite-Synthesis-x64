#############################################
#			Infinite Synthesis x64	  		#
#											#
# 파일 명: ./kernel/makefile					#
# 설명: Infinite Synthesis 빌드 용 makefile	#
# 최초 작성: 2020-04-03						#
#############################################
#			탭을 스페이스바로 입력하지 말 것.		#
#############################################

CC32=gcc -m32
CC64=gcc -m64
OCP=objcopy
LD32=ld -T ./elf_i386.x -nostdlib
LD64=ld -T ./elf_x86_64.x -nostdlib
CFLAGS=-c -masm=intel -ffreestanding -Wall
OFLAGS=-O binary -S -j .text -j .bss -j .data -j .rodata
INCLUDE32=../include/x86
INCLUDE64=../include
OBJ32=./init/init32.o ./x86/page.o ./x86/syscheck.o ../lib/x86/stdkernel.o
OBJ64=./init/init64.o ../lib/stdkernel64.o ./idt.o ./gdt.o ./pit.o ./shell/shell.o ./drivers/keyboard.o ./shell/sh_routine.o

all: kernel32 kernel64 drivers
kernel32: init32.o page.o syscheck.o
kernel64: gdt.o idt.o pit.o

###################32비트 커널 빌드###################
init32.o: ./init/init32.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./init/$@

page.o: ./x86/page.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./x86/$@

syscheck.o: ./x86/syscheck.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o ./x86/$@
	
###################64비트 커널 빌드###################
gdt.o: gdt.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o $@
	
idt.o: idt.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o $@
	
pit.o: pit.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o $@
	
drivers: ./drivers/makefile
	cd drivers; $(MAKE)

shell: ./shell/makefile
	cd shell; $(MAKE)
	
######################커널 이미지 빌드####################
Kernel32N.img: $(OBJ32)
	$(LD32) $(OBJ32) -o ../$@
	
Kernel32.img: ../Kernel32N.img
	$(OCP) $(OFLAGS) ../$^ ../$@

Kernel64N.img: $(OBJ64)
	$(LD64) $(OBJ64) -o ../$@
	
Kernel64.img: ../Kernel64N.img
	$(OCP) $(OFLAGS) ../$^ ../$@
	
.PHONY: clean

clean:
	rm -f ./*.o