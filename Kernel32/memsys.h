/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: memsys.h
 설명: 메모리에 관련된 함수 및 매크로 정의  
 최초 작성: 2019-01-30 						
********************************************/

#define PAGE_FLAGS_P        0x00000001  // Present
#define PAGE_FLAGS_RW       0x00000002  // Read/Write
#define PAGE_FLAGS_US       0x00000004  // User/Supervisor(플래그 설정 시 유저 레벨)
#define PAGE_FLAGS_PWT      0x00000008  // Page Level Write-through
#define PAGE_FLAGS_PCD      0x00000010  // Page Level Cache Disable
#define PAGE_FLAGS_A        0x00000020  // Accessed
#define PAGE_FLAGS_D        0x00000040  // Dirty
#define PAGE_FLAGS_PS       0x00000080  // Page Size
#define PAGE_FLAGS_G        0x00000100  // Global
#define PAGE_FLAGS_PAT      0x00001000  // Page Attribute Table Index

// 상위 32비트 용 속성 필드
#define PAGE_FLAGS_EXB      0x80000000  // Execute Disable 비트  
// 아래는 편의를 위해 정의한 플래그
#define PAGE_FLAGS_DEFAULT  ( PAGE_FLAGS_P | PAGE_FLAGS_RW )

void initPaging();

