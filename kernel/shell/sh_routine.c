/********************************************
 			Infinite Synthesis x64			
 											
 ���� ��: sh_routine.c			
 ����: Synthesis Shell�� ��ɾ ���� ��ƾ ����
 ���� �ۼ�: 2019-03-13 						
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
