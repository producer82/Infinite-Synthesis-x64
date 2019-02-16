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