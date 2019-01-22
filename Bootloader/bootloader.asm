;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			Infinite Synthesis x64			;
;											;
;파일 명: bootloader.asm						;
;설명: Infinite Synthesis의 기본 부트로더		;
;최초 작성: 2019-01-22 						;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[ORG 0x00]
[BITS 16]

section .text

jmp 0x07C0:MAIN

;메인 함수
MAIN:
	mov ax, cs	; DS = CS
	mov ds, ax
	xor ax, ax
	
	jmp $

;510 바이트까지 제로 필
times 510 - ($ - $$) db 0x00

;부트로더 시그니쳐
db 0x55
db 0xAA 
	

	

	
