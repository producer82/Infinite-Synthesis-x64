/********************************************
 			Infinite Synthesis x64			
 											
 ���� ��: stdkernel.c		
 ����: 32��Ʈ Ŀ���� ���� ���̺귯��
 ���� �ۼ�: 2019-02-15 						
********************************************/

#include "stdkernel.h"

// ���ڿ��� ȭ�鿡 ������ִ� �Լ�, printf()�� ���
void print(char* str, int line, int column, unsigned char color) {
	// ���� �޸� �ּ� = 0xB8000
	// �� ���� = 2 ����Ʈ, �� �� = 160 ����Ʈ
	char *video = (char*)(0xB8000 + 160 * line + (column * 2));	
	
	for (int i = 0; str[i] != 0; i++)
	{		
		*video++ = str[i];
		*video++ = color;
	}
}

void clearLine(unsigned char line, unsigned char column){
	char *video = (char*)(0xB8000 + 160 * line + (column * 2));
	
	for(int i=0; i<160 - column * 2; i++){
		*video++ = 0;
	}
}