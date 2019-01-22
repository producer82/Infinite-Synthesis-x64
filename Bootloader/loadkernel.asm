;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			Infinite Synthesis x64			;
;											;
;파일 명: loadkernel.asm						;
;설명: Infinite Synthesis의 기본 커널로더		;
;최초 작성: 2019-01-22 						;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  	  어셈블리 단위의 작업을 위한 미래 예약용	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[ORG 0x10000]
[BITS 32]

PROTECTED:
	mov ax, 0x20 ;세그먼트 셀렉터 초기화
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	mov ebp, 0xFFFE	;스택 초기화
	mov esp, 0xFFFE

LOADKERNEL:
	jmp 0x10200
	
times 512 - ($-$$) db 0