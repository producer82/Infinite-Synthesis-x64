#############################################
#			Infinite Synthesis x64	  		#
#											#
# 파일 명: makefile							#
# 설명: Infinite Synthesis 빌드 용 makefile	#
# 최초 작성: 2019-01-22						#
#############################################
#			탭을 스페이스바로 입력하지 말 것.	#
#############################################

CC32=gcc -m32
CC64=gcc -m64
CFLAGS=-c -masm=intel -ffreestanding
INCLUDE32=./include/x86
INCLUDE64=./include
NASM=nasm -f bin

all: bootloader library kernel Disk.img clean

###########################부트로더 빌드###########################
bootloader: ./boot/makefile
	cd boot; $(MAKE)
	
##########################라이브러리 빌드##########################
library: ./lib/makefile
	cd lib; $(MAKE)

############################커널 빌드###########################	
kernel: ./kernel/makefile
	cd kernel; $(MAKE)
	
###########################운영체제 이미지 빌드###########################	
Disk.img: ./boot/boot.bin Kernel32.img Kernel64.img
	cat ./boot/boot.bin Kernel32.img Kernel64.img > Disk.img
	
.PHONY: kernel clean
	
clean:
	find ./ -name '*.o' -exec rm {} \;
