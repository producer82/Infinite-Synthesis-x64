#include "stdkernel.h"

void Kernel64main(){
	__asm__ __volatile__(
		"mov ax, 0x10;"
		"mov ds, ax;"
		"mov es, ax;"
		"mov fs, ax;"
		"mov gs, ax;"
		"mov ss, ax;"
	);
	
	while(1);
}