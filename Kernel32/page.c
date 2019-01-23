#include "stdkernel.h"
#include "memsys.h"

#define P					0x01
#define RW 				0x02
#define PAGE_TABLE_SIZE	0x1000

void initPage(){
	PML4 *pml4 = (PML4*)0x100000;
	PDPT *pdpt = (PDPT*)0x101000;
	PDP *pdp = (PDP*)0x102000;
	
	//페이지 맵 레벨 4 테이블 설정
	setPageEntry(&(pml4[0]), 0x101000, 0, 0, P | RW);
	for(int i=1; i<512; i++){
		setPageEntry(&(pml4[i]), 0, 0, 0, 0);
	}
	
	//페이지 디렉터리 포인터 테이블 설정
	for(int i=0; i<64; i++){
		setPageEntry(&(pdpt[i]), (0x102000 + (i * PAGE_TABLE_SIZE)), 0, 0, P | RW);
	}
	
	for(int i=64; i<512; i++){
		setPageEntry(&(pdpt[i]), 0, 0, 0, 0);
	}
	
	//페이지 디렉터리 설정
	for(int i=0; i<64; i++){
		for(int j=0; j<512; j++){
			setPageEntry(&(pdp[j+(i * 512)]), PAGE_TABLE_SIZE * (j + (i * 512)), (i * (PAGE_TABLE_SIZE >> 20)) >> 12, 0, P | RW);
		}
	}
	
	__asm__ __volatile__(
		//CR3.PAE(5) 활성화
		"mov eax, cr4;"
		"or eax, 0x20;"
		"mov cr4, eax;"
	
		//PML4 로드
		"mov eax, 0x100000;"
		"mov cr3, eax;"
		
		//CR0.PG(31) 활성화
		"mov eax, cr0;"
		"or eax, 0x80000000;"
		"mov cr0, eax;"
	);
}

void setPageEntry(PageEntry *entry, unsigned int lowerAddress, unsigned int higherAddress, unsigned char higherFlag, unsigned char lowerFlag){
	entry->lowerAddressAndAttribute = lowerAddress | lowerFlag;
	entry->higherAddressAndExd = higherAddress | higherFlag;
}