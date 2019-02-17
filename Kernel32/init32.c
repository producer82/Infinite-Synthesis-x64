/********************************************
 			Infinite Synthesis x64			
 											
 ���� ��: init32.c			
 ����: 32��Ʈ Ŀ���� ����
 ���� �ۼ�: 2019-02-15 						
*********************************************
* 32��Ʈ Ŀ���� �ڵ带 ������ ��� moveKernel()�� 
* srcAddress���� �������־�� �մϴ�.
*********************************************/


#include "stdkernel.h"
#include "memsys.h"
#include "syscheck.h"

void Kernel32main(){
	// �޸� üũ
	if(isMemEnough())
		print("Memory Size Check ................... [OK]", 1, 0, 0x0F);
	else{
		print("Memory Size Check ................... [FAIL]", 1, 0, 0x0F);
		print("Infinite Synthesis need more than 64Mbyte", 2, 0, 0x0F);
		while(1);
	}
	
	// 64��Ʈ ���� Ȯ��
	isSupportLongMode();
	print("64bit Support Check ................. [OK]", 2, 0, 0x0F);
	
	// ������ ���̺� �ʱ�ȭ
	initPaging();
	print("Paging Initialize ................... [OK]", 3, 0, 0x0F);
	
	// Ŀ�� ����
	moveKernel();
	print("Kernel Copy ......................... [OK]", 4, 0, 0x0F);
	
	enableLongMode();
}

/********************************************
 srcAddress�� 64bit Kernel �������� ���ۺκ���
 �����ϴ� �������Դϴ�. ���� 32��Ʈ Ŀ���� ������ ���
 64��Ʈ Ŀ���� ��ġ ���� �̵��ϱ� ������ GDB�� Ȯ�� ��
 �������־�� �մϴ�.
 (32��Ʈ Ŀ���� ������ �ٷ� �ڿ� 64��Ʈ Ŀ�� �����Ͱ� �پ�����)
********************************************/

void moveKernel(){
	unsigned int *srcAddress;
	unsigned int *destAddress;
	unsigned int *checksum;
	
	srcAddress = (unsigned int*)0x10692;
	destAddress = (unsigned int*)0x200000;
	checksum = (unsigned int*)srcAddress++;
	
	while(*srcAddress != 0 || *checksum != 0){
		*destAddress = *srcAddress;
		destAddress++;
		srcAddress++;
		checksum++;
	}
}

void enableLongMode(){
	__asm__ __volatile__(	
		//cr3 = pageMapLevel4
		"mov eax, 0x100000;"
		"mov cr3, eax;"
		
		//IA-32e Ȱ��ȭ
		"mov ecx, 0xC0000080;"
		"rdmsr;"
		"or eax, 1 << 8;"
		"wrmsr;"
	
		//CR3.PAE(5) Ȱ��ȭ
		"mov eax, cr4;"
		"or eax, 0x20;"
		"mov cr4, eax;"
		
		//CR0.PG(31) Ȱ��ȭ
		"mov eax, cr0;"
		"or eax, 1 << 31;"
		"mov cr0, eax;"
		
		//CS = 0x18 (IA-32e CODE)
		"jmp  0x18:0x200000"
	);
}

