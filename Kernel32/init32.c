/********************************************
			Infinite Synthesis x64			
			
���� ��: init32.c
����: 32��Ʈ Ŀ�� ����
���� �ۼ�: 2019-01-23
********************************************/

#include "stdkernel.h"
#include "memsys.h"

void Kernel32main() {
	print("Infinite Synthesis Startup", 0, 0, 0x0E);
	//����¡ Ȱ��ȭ
	initPage();        
	//64��Ʈ Ŀ�� ����
	moveKernel();
	//IA-32e Ȱ��ȭ
	enteringLongMode();
	//64��Ʈ Ŀ�η� �̵�
	__asm__ __volatile__("jmp 0x08:0x200000");
}

void moveKernel(){
	unsigned int *srcAddress;
	unsigned int *destAddress;
	unsigned int *checksum;
	
	srcAddress = (unsigned int*)0x1035A;
	destAddress = (unsigned int*)0x200000;
	checksum = (unsigned int*)srcAddress++;
	
	while(*srcAddress != 0 || *checksum != 0){
		*destAddress = *srcAddress;
		destAddress++;
		srcAddress++;
		checksum++;
	}
}

void enteringLongMode(){
	__asm__ __volatile__(
		//CR3.PAE(5) Ȱ��ȭ
		"mov eax, cr4;"
		"or eax, 0x20;"
		"mov cr4, eax;"
	
		//PML4 �ε�
		"mov eax, 0x100000;"
		"mov cr3, eax;"
		
		//IA32_EFER.LME(8) Ȱ��ȭ
		"mov ecx, 0xC0000080;"
		"rdmsr;"
		"or eax, 1 << 8;"
		"wrmsr;"

		//CR0.NW(29), CR0.CD(30) ��Ȱ��ȭ
		//CR0.PG(31) Ȱ��ȭ
		"mov eax, cr0;"
		"or eax, 1 << 29;"
		"or eax, 1 << 30;"
		"or eax, 1 << 31;"

		"xor eax, 1 << 29;"
		"xor eax, 1 << 30;"

		"mov cr0, eax;"
	);
}