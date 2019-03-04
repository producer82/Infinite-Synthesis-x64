/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: page.c			
 설명: 페이징에 필요한 테이블을 초기화하고 활성화 함
 최초 작성: 2019-01-30 						
********************************************/

#include "memsys.h"

void initPaging()
{
	// unsigned long long -> 64비트 정수형
	// unsigned long 사용시 메모리에서 32비트 단위로 처리됨.
	unsigned long long* PML4Entry;
	unsigned long long* PDPTEntry;
	unsigned long long* PDEntry;

	// PML4 테이블 맵핑
	PML4Entry = (unsigned long long*)0x100000;
    PML4Entry[0] = (unsigned long long)0x101000 | PAGE_FLAGS_DEFAULT;

	// 페이지 디렉터리 포인터 테이블 맵핑
	PDPTEntry = (unsigned long long*)0x101000;
    for(int i = 0; i < 512; i++) {
		PDPTEntry[i] = (unsigned long long)0x102000 + (i * 0x1000) | PAGE_FLAGS_DEFAULT;
    }

	// 페이지 디렉터리 테이블 맵핑
    PDEntry = ( unsigned long long* ) 0x102000;
    for(int i = 0; i < 512 * 64; i++)
    {
		PDEntry[i] = (unsigned long long)0x200000 * i | PAGE_FLAGS_DEFAULT | PAGE_FLAGS_PS;
    }
	

}
