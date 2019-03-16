#include "shell.h"
#include "shroutine.h"
#include "stdkernel.h"

unsigned char shellLine = 1;
unsigned char *at = "Synthesis>";

extern unsigned char data;

void enterShell(){
	clear();
	
	// 키보드로 엔터가 입력되는것을 인터럽트를 통해 감지하면
	// 아래 루틴을 수행하여 입력을 처리한다.
	while(1){
		
	}
}