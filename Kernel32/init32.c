/********************************************
			Infinite Synthesis x64			
			
파일 명: init32.c
설명: 32비트 커널 메인
최초 작성: 2019-01-23
********************************************/

#include "stdkernel.h"
#include "memsys.h"

void Kernel32main() {
	print("Infinite Synthesis Startup", 0, 0, 0x0E);
	//페이징 활성화
	initPage();        
	//64비트 커널 복사
	moveKernel();
	//IA-32e 활성화
	enteringLongMode();
	//64비트 커널로 이동
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
		//CR3.PAE(5) 활성화
		"mov eax, cr4;"
		"or eax, 0x20;"
		"mov cr4, eax;"
	
		//PML4 로드
		"mov eax, 0x100000;"
		"mov cr3, eax;"
		
		//IA32_EFER.LME(8) 활성화
		"mov ecx, 0xC0000080;"
		"rdmsr;"
		"or eax, 1 << 8;"
		"wrmsr;"

		//CR0.NW(29), CR0.CD(30) 비활성화
		//CR0.PG(31) 활성화
		"mov eax, cr0;"
		"or eax, 1 << 29;"
		"or eax, 1 << 30;"
		"or eax, 1 << 31;"

		"xor eax, 1 << 29;"
		"xor eax, 1 << 30;"

		"mov cr0, eax;"
	);
}