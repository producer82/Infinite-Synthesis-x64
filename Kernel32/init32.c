/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: init32.c			
 설명: 32비트 커널의 메인
 최초 작성: 2019-02-15 						
*********************************************
* 32비트 커널의 코드를 수정할 경우 moveKernel()의 
* srcAddress값을 변경해주어야 합니다.
*********************************************/


#include "stdkernel.h"
#include "memsys.h"
#include "syscheck.h"

void Kernel32main(){
	// 메모리 체크
	if(isMemEnough())
		print("Memory Size Check ................... [OK]", 1, 0, 0x0F);
	else{
		print("Memory Size Check ................... [FAIL]", 1, 0, 0x0F);
		print("Infinite Synthesis need more than 64Mbyte", 2, 0, 0x0F);
		while(1);
	}
	
	// 64비트 지원 확인
	isSupportLongMode();
	print("64bit Support Check ................. [OK]", 2, 0, 0x0F);
	
	// 페이지 테이블 초기화
	initPaging();
	print("Paging Initialize ................... [OK]", 3, 0, 0x0F);
	
	// 커널 복사
	moveKernel();
	print("Kernel Copy ......................... [OK]", 4, 0, 0x0F);
	
	enableLongMode();
}

/********************************************
 srcAddress는 64bit Kernel 데이터의 시작부분을
 지시하는 포인터입니다. 따라서 32비트 커널이 수정될 경우
 64비트 커널의 위치 또한 이동하기 때문에 GDB로 확인 후
 수정해주어야 합니다.
 (32비트 커널의 데이터 바로 뒤에 64비트 커널 데이터가 붙어있음)
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
		
		//IA-32e 활성화
		"mov ecx, 0xC0000080;"
		"rdmsr;"
		"or eax, 1 << 8;"
		"wrmsr;"
	
		//CR3.PAE(5) 활성화
		"mov eax, cr4;"
		"or eax, 0x20;"
		"mov cr4, eax;"
		
		//CR0.PG(31) 활성화
		"mov eax, cr0;"
		"or eax, 1 << 31;"
		"mov cr0, eax;"
		
		//CS = 0x18 (IA-32e CODE)
		"jmp  0x18:0x200000"
	);
}

