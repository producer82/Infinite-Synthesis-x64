/********************************************
 			Infinite Synthesis x64			
 											
 ���� ��: page.c			
 ����: 32��Ʈ Ŀ���� ����
 ���� �ۼ�: 2019-02-15 						
********************************************/

#include "stdkernel.h"
#include "memsys.h"
#include "syscheck.h"

void Kernel32main(){
	// �޸� üũ
	if(isMemEnough())
		print("Memory Size Check ................... [OK]", 1, 0, 0x0F);
	else{
		print("Memory Size Check ................... [FAIL]", 1, 0, 0x0F);
		print("Infinite Synthesis need more than 64Mbyte", 2, 0, 0x0F);
		while(1);
	}
	
	// 64��Ʈ ���� Ȯ��
	isSupportLongMode();
	print("64bit Support Check ................. [OK]", 2, 0, 0x0F);
	
	// ������ ���̺� �ʱ�ȭ
	initPaging();
	print("Paging Initialize ................... [OK]", 3, 0, 0x0F);
	
	moveKernel();
	while(1);
}

void moveKernel(){
	unsigned int *srcAddress;
	unsigned int *destAddress;
	unsigned int *checksum;
	
	srcAddress = (unsigned int*)0x10200;
	destAddress = (unsigned int*)0x200000;
	checksum = (unsigned int*)srcAddress++;
	
	while(srcAddress != 0 || checksum != 0){
		*destAddress = *srcAddress;
		destAddress++;
		srcAddress++;
		checksum++;
	}
}

