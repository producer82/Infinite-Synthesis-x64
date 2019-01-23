#pragma once

typedef struct pageStruct{
	unsigned int lowerAddressAndAttribute;
	unsigned int higherAddressAndExd;
}__attribute__((packed)) PML4, PDPT, PDP, PD, PageEntry;

void setPageEntry(PageEntry*, unsigned int, unsigned int, unsigned char, unsigned char);
void initPage();