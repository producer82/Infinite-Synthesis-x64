;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			Infinite Synthesis x64			;
;											;
;���� ��: bootloader.asm						;
;����: Infinite Synthesis�� �⺻ ��Ʈ�δ�		;
;���� �ۼ�: 2019-01-22 						;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[ORG 0x00]
[BITS 16]

section .text

jmp 0x07C0:MAIN

;���� �Լ�
MAIN:
	mov ax, cs	; DS = CS
	mov ds, ax
	xor ax, ax
	
	jmp $

;510 ����Ʈ���� ���� ��
times 510 - ($ - $$) db 0x00

;��Ʈ�δ� �ñ״���
db 0x55
db 0xAA 
	

	

	
