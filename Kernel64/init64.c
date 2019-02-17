/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: init64.c
 설명: 64비트 커널의 메인
 최초 작성: 2019-02-16 						
********************************************/

#include "stdkernel.h"

void Kernel64main(){
	__asm__ __volatile__ (
		"mov ax, 0x20;"
		"mov ds, ax;"
		"mov es, ax;"
		"mov gs, ax;"
		"mov fs, ax;"
		"mov ss, ax;"
	);
	
	print("Load 64bit Kernel ................... [OK]", 5, 0, 0x0F);
	
	
	
	while(1);
}