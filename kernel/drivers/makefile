#############################################
#			Infinite Synthesis x64	  		#
#											#
# 파일 명: ./kernel/drivers/makefile			#
# 설명: Infinite Synthesis 빌드 용 makefile		#
# 최초 작성: 2020-04-04							#
#############################################
#			탭을 스페이스바로 입력하지 말 것.			#
#############################################

CC=gcc -m64
CFLAGS=-c -masm=intel -ffreestanding -Wall
INCLUDE=../../include

all: hdd.o keyboard.o

hdd.o: hdd.c
	$(CC) $(CFLAGS) -I$(INCLUDE) $^ -o $@
	
keyboard.o: keyboard.c
	$(CC) $(CFLAGS) -I$(INCLUDE) $^ -o $@
	
.PHONY: clean

clean:
	rm -f *.img