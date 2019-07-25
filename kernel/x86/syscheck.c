/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: syscheck.c		
 설명: 운영체제가 기동될 수 있는지 판단하기 위해 시스템을 확인함
 최초 작성: 2019-02-15 						
********************************************/

#include "stdkernel.h"
#include "syscheck.h"

// 메모리의 크기가 64MB 이상인지 확인
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

// 64비트를 지원하는지 확인
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
