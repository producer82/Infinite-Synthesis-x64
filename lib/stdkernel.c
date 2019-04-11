/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: stdkernel.c		
 설명: 32비트 커널을 위한 라이브러리
 최초 작성: 2019-02-15 						
********************************************/

#include "stdkernel.h"

// 문자열 출력
void print(char* str, int line, int column, unsigned char color) {
	char *video = (char*)(0xB8000 + 160 * line + (column * 2));	
	
	for (int i = 0; str[i] != 0; i++)
	{		
		*video++ = str[i];
		*video++ = color;
	}
}

// 화면 초기화
void clear(){
	char *video = (char*)0xB8000;
	
	for (int i = 0; i < 80 * 25 * 2; i++){
		*video++ = 0;
	}
}

// 줄 단위의 초기화
void clearLine(unsigned char line, unsigned char column){
	char *video = (char*)(0xB8000 + 160 * line + (column * 2));
	
	for(int i=0; i<160 - column * 2; i++){
		*video++ = 0;
	}
}

char strcmp(char *str1, char *str2){
	int i = 0;
	while(str1[i] != 0 || str2[i] != 0){
		if(str1[i] != str2[i]){
			return 0;
		}
		i++;
	}
	return 1;
}
