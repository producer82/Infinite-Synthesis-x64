[ORG 0x10000]
[BITS 32]

PROTECTED:
	mov ax, 0x10
	mov gs, ax
	mov ss, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	
	mov ebp, PROTECTED
	mov esp, PROTECTED

	mov ebx, 0			; �ż��� ��� �غ�
	lea esi, [message]
	push es				; es�� ����ִ� �����ͼ��� ���� ������
	mov ax, 0x28 ; ���� ���׸�Ʈ �� �ְ�
	mov es, ax
	mov ah, 0x0E

MESSAGE:
	lodsb
	mov byte [es:ebx], al	;���� �޸�:EDI�� al �ְ�
	inc ebx					;���� �޸� ������ �ø���
	mov byte [es:ebx], ah	;�Ӽ��� �ְ�
	inc ebx					;edi �ø��� 
	cmp al, 0				;0���� Ȯ���ϰ�
	jz LOADKERNEL
	jmp MESSAGE

LOADKERNEL:
	pop es
	jmp dword 0x08:0x10200

message: db 'Infinite Synthesis Kernel Start', 0

times 512 - ($ - $$) db 0x00