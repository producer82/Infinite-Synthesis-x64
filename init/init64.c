/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: init64.c
 설명: 64비트 커널의 메인
 최초 작성: 2019-02-16 						
********************************************/

#include "stdkernel.h"
#include "descriptor.h"
#include "drivers.h"
#include "shell.h"

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
	
	initInterrupt();
	print("Interrupt Setting ................... [OK]", 6, 0, 0x0F);
	
	initKeyboard();
	print("Setting for I/O Device .............. [OK]", 7, 0, 0x0F);
	
	//initFileSystem();
	print("Load File System .................... [OK]", 8, 0, 0x0F);
	
	enterShell();
	
	while(1);
}