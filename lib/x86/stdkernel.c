/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: stdkernel.c		
 설명: 32비트 커널을 위한 라이브러리
 최초 작성: 2019-02-15 						
********************************************/

#include "stdkernel.h"

// 문자열을 화면에 출력해주는 함수, printf()의 기능
void print(char* str, int line, int column, unsigned char color) {
	// 비디오 메모리 주소 = 0xB8000
	// 한 문자 = 2 바이트, 한 줄 = 160 바이트
	char *video = (char*)(0xB8000 + 160 * line + (column*2) );
	
	for (int i = 0; str[i] != 0; i++)
	{		
		*video++ = str[i];
		*video++ = color;
	}
}
