/********************************************
 			Infinite Synthesis x64			
 											
 ���� ��: interrupt.c			
 ����: ���ͷ�Ʈ ������ ���̺� ���� �� ISR �Լ�
 ���� �ۼ�: 2019-02-17 						
********************************************/

#include "descriptor.h"
#include "stdkernel.h"
#include "drivers.h"

char key[1] = {0};				//Ÿ�̸� ���ͷ�Ʈ Ȯ�ο� ����
extern char inputStr[200];		//�Է� ���ڿ� ���� �迭, keyboard.c
extern unsigned char shellLine;	//����� �� ���� ����, shell.c

void initInterrupt(){
	IDTR *idtr;
	IDT *intTableEntry;
	
	intTableEntry = (IDT*)0x0000;
	idtr = (IDTR*)(sizeof(IDT) * 256);
	
	idtr->limit = (sizeof(IDT) * 256) - 1;
	idtr->base = 0x0000;
	
	//���õǴ� ���ͷ�Ʈ�� ������
	for(int i = 0; i < 256; i++){
		setIDTEntry(&(intTableEntry[i]), isrDummy, 0x18, 0, IDT_PRESENT | IDT_INT_GATE);
	}

	//Divide by Zero ���ͷ�Ʈ
	setIDTEntry(&(intTableEntry[0]), isrDivideByZero, 0x18, 0, IDT_PRESENT | IDT_INT_GATE);
	
	//Ÿ�̸� ���ͷ�Ʈ
	setIDTEntry(&(intTableEntry[32]), isrTimer, 0x18, 0, IDT_PRESENT | IDT_INT_GATE);

	//Ű���� ���ͷ�Ʈ
	setIDTEntry(&(intTableEntry[33]), isrKeyboard, 0x18, 0, IDT_PRESENT | IDT_INT_GATE);
	
	// ���ͷ�Ʈ Ȱ��ȭ
	__asm__ __volatile__("mov rax, %0"::"r"(idtr));
	
	__asm__ __volatile__(
			"lidt [rax];"
			"mov al, 0xFC;"	// Ű����, Ÿ�̸� ���ͷ�Ʈ ����
			"out 0x21, al;"
			"sti;"
	);
}

void setIDTEntry(IDT *entry, void* isrAddress, unsigned short selector, unsigned char ist, unsigned char typeAndAttribute){
	entry->lowerOffset = (unsigned long) isrAddress & 0xFFFF;
	entry->selector = selector;
	entry->ist = ist;
	entry->typeAttr = typeAndAttribute;
	entry->middleOffset = ((unsigned long) isrAddress >> 16) & 0xFFFF;
	entry->higherOffset = ((unsigned long) isrAddress >> 32);
	entry->zerofill = 0;
}

void isrDummy(){
	saveStatus;
	restoreStatus;
}

void isrDivideByZero(){
	saveStatus;
	restoreStatus;
}

void isrTimer(){
	saveStatus;
	
	print(key, 24, 79, 0x0F);
	key[0]++;

	restoreStatus;
}

void isrKeyboard(){
	saveStatus;
	
	getInput();
	
	clearLine(shellLine, 10);
	print(inputStr, shellLine, 10, 0x0F);
	
	restoreStatus;
}
