/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: page.c			
 설명: 32비트 커널의 메인
 최초 작성: 2019-02-15 						
********************************************/

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
	
	moveKernel();
	while(1);
}

void moveKernel(){
	unsigned int *srcAddress;
	unsigned int *destAddress;
	unsigned int *checksum;
	
	srcAddress = (unsigned int*)0x10200;
	destAddress = (unsigned int*)0x200000;
	checksum = (unsigned int*)srcAddress++;
	
	while(srcAddress != 0 || checksum != 0){
		*destAddress = *srcAddress;
		destAddress++;
		srcAddress++;
		checksum++;
	}
}

