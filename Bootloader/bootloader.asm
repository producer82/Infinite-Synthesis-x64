;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			Infinite Synthesis x64			;
;											;
;파일 명: bootloader.asm						;
;설명: Infinite Synthesis의 부트로더			;
;최초 작성: 2019-01-22 						;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[ORG 0x00]
[BITS 16]

section .text

jmp 0x07C0:START	

START:
	mov ax, cs	; DS = CS
	mov ds, ax
	xor ax, ax
	
	
