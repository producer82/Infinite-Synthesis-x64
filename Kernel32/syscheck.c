/********************************************
 			Infinite Synthesis x64			
 											
 ���� ��: syscheck.c		
 ����: �ü���� �⵿�� �� �ִ��� �Ǵ��ϱ� ���� �ý����� Ȯ����
 ���� �ۼ�: 2019-02-15 						
********************************************/

#include "stdkernel.h"
#include "syscheck.h"

// �޸��� ũ�Ⱑ 64MB �̻����� Ȯ��
char isMemEnough(){
	unsigned int *memoryPtr;
	// 0x3D09000 = 64000000, 64MB
	memoryPtr = (unsigned int*)0x3D09000;
	*memoryPtr = 0x030819;
	
	if(*memoryPtr != 0x030819){
		return FALSE;	
	}
	
	return TRUE; 
}

// 64��Ʈ�� �����ϴ��� Ȯ��
void isSupportLongMode(){
	__asm__ __volatile__(
		"pushad;"
		
		"mov eax, 0x80000001;"
		"cpuid;"
		"test edx, 1 << 29;"
		"jz NotSupported;"
		
		"popad;"
	);
}

void NotSupported(){
	print("IA-32e Support Check ..............[NO]", 3, 0, 0x0F);
	print("CPU does not support 64 bits!", 4, 0, 0x0F);
	while(1);
}
