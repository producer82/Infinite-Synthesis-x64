/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: interrupt.c			
 설명: 인터럽트 서술자 테이블 설정 및 ISR 함수
 최초 작성: 2019-02-17 						
********************************************/

#include "descriptor.h"
#include "stdkernel.h"
#include "drivers.h"

char key[1] = {0};				//타이머 인터럽트 확인용 변수
extern char inputStr[200];		//입력 문자열 저장 배열, keyboard.c
extern unsigned char shellLine;	//출력할 줄 계산용 변수, shell.c

void initInterrupt(){
	IDTR *idtr;
	IDT *intTableEntry;
	
	intTableEntry = (IDT*)0x0000;
	idtr = (IDTR*)(sizeof(IDT) * 256);
	
	idtr->limit = (sizeof(IDT) * 256) - 1;
	idtr->base = 0x0000;
	
	//무시되는 인터럽트를 맵핑함
	for(int i = 0; i < 256; i++){
		setIDTEntry(&(intTableEntry[i]), isrDummy, 0x8, 0, IDT_PRESENT | IDT_INT_GATE);
	}

	//Divide by Zero 인터럽트
	setIDTEntry(&(intTableEntry[0]), isrDivideByZero, 0x8, 0, IDT_PRESENT | IDT_INT_GATE);
	
	//타이머 인터럽트
	setIDTEntry(&(intTableEntry[32]), isrTimer, 0x8, 0, IDT_PRESENT | IDT_INT_GATE);

	//키보드 인터럽트
	setIDTEntry(&(intTableEntry[33]), isrKeyboard, 0x8, 0, IDT_PRESENT | IDT_INT_GATE);
	
	// 인터럽트 활성화
	__asm__ __volatile__("mov rax, %0"::"r"(idtr));
	
	__asm__ __volatile__(
			"lidt [rax];"
			"mov al, 0xFC;"	// 키보드, 타이머 인터럽트 개방
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
