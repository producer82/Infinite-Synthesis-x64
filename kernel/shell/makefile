#############################################
#			Infinite Synthesis x64	  		#
#											#
# 파일 명: ./kernel/shell/makefile			#
# 설명: Infinite Synthesis 빌드 용 makefile	#
# 최초 작성: 2020-04-04						#
#############################################
#			탭을 스페이스바로 입력하지 말 것.		#
#############################################

CC=gcc -m64
CFLAGS=-c -masm=intel -ffreestanding -Wall
INCLUDE=../../include

all: shell.o sh_routine.o

shell.o: shell.c
	$(CC) $(CFLAGS) -I$(INCLUDE) $^ -o $@
	
sh_routine.o: sh_routine.c
	$(CC) $(CFLAGS) -I$(INCLUDE) $^ -o $@