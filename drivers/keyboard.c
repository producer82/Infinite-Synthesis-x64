/********************************************
 			Infinite Synthesis x64			
 											
 ���� ��: keyboard.c			
 ����: �⺻���� Ű���� ����̹�
 ���� �ۼ�: 2019-02-17 						
********************************************/

/****TODO****/
// �빮�� �Է�
// Ư������ �Է�
// LED ����
// Ȱ��ȭ�� ��Ʈ �˻�
/************/
#include "drivers.h"

// Ű���� �Է¿� ���̴� ����
char inputStr[200];
unsigned char data;
unsigned char index;

// Ű���� ��ġ Ȱ��ȭ
void initKeyboard(){
	__asm__ __volatile__ ("mov al, 0xAE");
	__asm__ __volatile__ ("out 0x64, al");
}

void isBufferFull(){
	
}

void getInput(){
	// �Է��� �޾� AL�� ������
	__asm__ __volatile__(
		"xor al, al;"
		"in al, 0x60;"
		"mov %0, al;":"=m"(data)
	);
	
	// ��ĵ�ڵ带 �ƽ�Ű �ڵ�� ��ȯ
	data = smallAsciiSet(data);
	
	// �� �����̽� �Է� ��
	if (data == 0x08 && index != 0){
		inputStr[--index] = 0;
	}
	
	// ���� �Է� ��
	else if (data != 0xFF && data != 0x08 && data != 0x0D){
		inputStr[index++] = data;
	}
}

// ��ĵ�ڵ� -> �ҹ��� �ƽ�Ű ��ȯ ���̺�
unsigned char smallAsciiSet(unsigned char data){
	switch(data){
		case(0x1E): return 'a'; break;
		case(0x30): return 'b'; break;
		case(0x2E): return 'c'; break;
		case(0x20): return 'd'; break;
		case(0x12): return 'e'; break;
		case(0x21): return 'f'; break;
		case(0x22): return 'g'; break;
		case(0x23): return 'h'; break;
		case(0x17): return 'i'; break;
		case(0x24): return 'j'; break;
		case(0x25): return 'k'; break;
		case(0x26): return 'l'; break;
		case(0x32): return 'm'; break;
		case(0x31): return 'n'; break;
		case(0x18): return 'o'; break;
		case(0x19): return 'p'; break;
		case(0x10): return 'q'; break;
		case(0x13): return 'r'; break;
		case(0x1F): return 's'; break;
		case(0x14): return 't'; break;
		case(0x16): return 'u'; break;
		case(0x2F): return 'v'; break;
		case(0x11): return 'w'; break;
		case(0x2D): return 'x'; break;
		case(0x15): return 'y'; break;
		case(0x2C): return 'z'; break;
		case(0x39): return ' '; break;
		case(0xE): return 0x8; break;
		case(0x1C): return 0xD; break;
		default: return 0xFF; break;
	}
}
