;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			Infinite Synthesis x64			;
;											;
;���� ��: bootloader.asm						;
;����: Infinite Synthesis�� ��Ʈ�δ�			;
;���� �ۼ�: 2019-01-22 						;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[ORG 0x00]
[BITS 16]

section .text

jmp 0x07C0:START	

START:
	mov ax, cs	; DS = CS
	mov ds, ax
	xor ax, ax
	
	
