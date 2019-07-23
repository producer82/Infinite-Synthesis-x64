#include "descriptor.h"
#define NUMBER_OF_ENTRYS 3

void initGDT(){
	GDTR *gdtr = (GDTR*)0x150000;
	GDT *gdtEntry = (GDT*)(0x150000 + sizeof(GDTR));

	gdtr->size = sizeof(GDT) * NUMBER_OF_ENTRYS - 1;
	gdtr->offset = (unsigned long)gdtEntry;
	
	//Null Descriptor 생성
	setGDTEntry(&(gdtEntry[0]), 0, 0, 0, 0);
	//Code Descriptor 생성
	setGDTEntry(&(gdtEntry[1]), 0, 0xFFFFF, 0x9A, 0xA0);
	//Data Descriptor 생성
	setGDTEntry(&(gdtEntry[2]), 0, 0xFFFFF, 0x92, 0xA0);
	
	__asm__ __volatile__("cli");
	__asm__ __volatile__("mov rax, 0x150000");
	__asm__ __volatile__("lgdt [rax]");	
	
	__asm__ __volatile__ (
		"mov ax, 0x8;"
		"mov ds, ax;"
		"mov es, ax;"
		"mov gs, ax;"
		"mov fs, ax;"
		"mov ss, ax;"
	);
	
	__asm__ __volatile__("GDT_END:");
	
}

void setGDTEntry(GDT *entry, unsigned int baseAddress, unsigned int limitAddress, unsigned char accessByte, unsigned char flags){
	entry->lowerLimitAddress = (limitAddress & 0xFFFF);
	entry->lowerBaseAddress = (baseAddress & 0xFFFF);
	entry->middleBaseAddress = (baseAddress >> 16) & 0xFF;
	entry->accessByte = accessByte;
	entry->higherLimitAndFlags = ((limitAddress >> 16) & 0xF) | flags;
	entry->higherBaseAddress = (baseAddress >> 24) & 0xFF;
}

