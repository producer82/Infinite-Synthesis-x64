#include "descriptor.h"

void initGDT(){
	int numberOfEntry;

	GDT *gdtEntry = (unsigned long*)0x105000;
	GDTR *gdtr = (unsigned long*)(0x105000 + sizeof(gdtEntry) * numberOfEntry);

	gdtr->size = sizeof(gdtEntry) * numberOfEntry - 1;
	gdtr->offset = gdtEntry;

	
}

void setGDTEntry(GDT *entry, unsigned long* baseAddress, unsigned long* upperAddress, unsigned char flag){

}