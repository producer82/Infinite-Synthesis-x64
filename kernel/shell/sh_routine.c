/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: sh_routine.c			
 설명: Synthesis Shell의 명령어를 위한 루틴 모음
 최초 작성: 2019-03-13 						
********************************************/

#include "stdkernel.h"
#include "shell.h"

extern unsigned char shellLine;

void osVersion(){
	print("--------===========Infinite Synthesis x64 Alpha===========--------", shellLine, 7, 0x0F);
	processScroll();
	print("                      Synthesis Shell Alpha", shellLine, 7, 0x0F);
	processScroll();
}
