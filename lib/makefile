#############################################
#			Infinite Synthesis x64	  		#
#											#
# 파일 명: ./kernel/shell/makefile			#
# 설명: Infinite Synthesis 빌드 용 makefile	#
# 최초 작성: 2020-04-04						#
#############################################
#			탭을 스페이스바로 입력하지 말 것.		#
#############################################

CC32=gcc -m64
CC64=gcc -m32
CFLAGS=-c -masm=intel -ffreestanding -Wall
INCLUDE64=../include
INCLUDE32=../include/x86

all: ./x86/stdkernel.o stdkernel.o

./x86/stdkernel.o: ./x86/stdkernel.c
	$(CC32) $(CFLAGS) -I$(INCLUDE32) $^ -o $@
	
stdkernel.o: stdkernel.c
	$(CC64) $(CFLAGS) -I$(INCLUDE64) $^ -o $@
	
.PHONY: clean

clean:
	rm -f *.o