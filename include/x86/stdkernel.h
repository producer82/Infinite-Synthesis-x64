/********************************************
 			Infinite Synthesis x64			
 											
 파일 명: stdkernel.h
 설명: 32비트 커널을 위한 라이브러리 헤더파일
 최초 작성: 2019-02-15 						
********************************************/


#define TRUE 1
#define FALSE 0
#define bool unsigned 

void print(char* str, int line, int column, unsigned char color);
void moveKernel();
void enableLongMode();