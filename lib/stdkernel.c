/********************************************
 			Infinite Synthesis x64			
 											
 ���� ��: stdkernel.c		
 ����: 32��Ʈ Ŀ���� ���� ���̺귯��
 ���� �ۼ�: 2019-02-15 						
********************************************/

#include "stdkernel.h"

// ���ڿ� ���
void print(char* str, int line, int column, unsigned char color) {
	char *video = (char*)(0xB8000 + 160 * line + (column * 2));	
	
	for (int i = 0; str[i] != 0; i++)
	{		
		*video++ = str[i];
		*video++ = color;
	}
}

// ȭ�� �ʱ�ȭ
void clear(){
	char *video = (char*)0xB8000;
	
	for (int i = 0; i < 80 * 25 * 2; i++){
		*video++ = 0;
	}
}

// �� ������ �ʱ�ȭ
void clearLine(unsigned char line, unsigned char column){
	char *video = (char*)(0xB8000 + 160 * line + (column * 2));
	
	for(int i=0; i<160 - column * 2; i++){
		*video++ = 0;
	}
}