/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: shell.c			
 설명: Synthesis Shell의 메인
 최초 작성: 2019-03-09 						
********************************************/

#include "shell.h"
#include "sh_routine.h"
#include "stdkernel.h"

unsigned char shellLine = 0;
extern unsigned char inputStr[160];
extern unsigned char keyboardIndex;
extern unsigned char data;
char *at = "Synthesis>";

void enterShell(){
	clear();
	osVersion();
	processScroll();
	print("Synthesis>", shellLine, 0, 0x09);
	// 키보드로 엔터가 입력되는것을 인터럽트를 통해 감지하면
	// 아래 루틴을 수행하여 입력을 처리한다.
	while(1){
		if(data == 0x0D){
			//interpreteCommand();
			processScroll();
			print("Synthesis>", shellLine, 0, 0x09);
			data = 0;
			keyboardIndex = 0;
			for(int i = 0; i < 160; i++){
				inputStr[i] = 0;
			}
		}
	}
}

<<<<<<< HEAD
void interpreteCommand(){
	;
=======
void interpretCommand(){
	if(strcmp(inputStr, "help")){
		comHelp();
	}
	else if(strcmp(inputStr, "version")){
		comVersion();
	}
	else{
		print("Synthesis: command not found", shellLine, 0, 0x0E);
	}
>>>>>>> d3a118aec8a4c64269facc19324a0a2eb97035aa
}

void processScroll(){
	if (shellLine < 24){
		shellLine++;
	}
	if (shellLine > 23){
		scroll();
	}
}

void scroll(){
	unsigned short *video = (unsigned short*)0xB8000;
	for(int i = 0; i < 25; i++){
		for(int j = 0; j < 80; j++){
			video[i * 80 + j] = video[(i+1) * 80 + j];
		}
	}
}
