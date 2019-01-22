;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;			Infinite Synthesis x64			;
;											;
;���� ��: loadkernel.asm						;
;����: Infinite Synthesis�� �⺻ Ŀ�ηδ�		;
;���� �ۼ�: 2019-01-22 						;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;  	  ����� ������ �۾��� ���� �̷� �����	;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

[ORG 0x10000]
[BITS 32]

PROTECTED:
	mov ax, 0x20 ;���׸�Ʈ ������ �ʱ�ȭ
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	mov ebp, 0xFFFE	;���� �ʱ�ȭ
	mov esp, 0xFFFE

LOADKERNEL:
	jmp 0x10200
	
times 512 - ($-$$) db 0