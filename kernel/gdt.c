#include "descriptor.h"

#define NUMBER_OF_ENTRYS 3

void initGDT(){
	GDTR *gdtr = (unsigned long*)0x150000;
	GDT *gdtEntry = (unsigned long*)(0x150000 + (sizeof(GDTR)));

	gdtr->size = sizeof(gdtEntry) * NUMBER_OF_ENTRYS - 1;
	gdtr->offset = gdtEntry;
	
	//Null Descriptor 생성
	setGDTEntry(gdtEntry[0], 0, 0, 0, 0);
}

void setGDTEntry(GDT *entry, unsigned long* baseAddress, unsigned long* limitAddress, unsigned char accessByte, unsigned char flags){
	entry->lowerLimitAddress = limitAddress & 0xFFFF;
	entry->lowerBaseAddress = baseAddress & 0xFFFF;
	entry->middleBaseAddress = (baseAddress >> 16) & 0xFF;
	entry->accessByte = accessByte;
	entry->higherLimitAndFlags = ((limitAddress >> 16) & 0xF) | flags;
	entry->higherBaseAddress = (baseAddress >> 24) & 0xFF;
}