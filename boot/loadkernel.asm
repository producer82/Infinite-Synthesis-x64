[ORG 0x10000]
[BITS 32]

PROTECTED:
	
	mov ax, 0x20
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
	jz PICINIT
	jmp MESSAGE
	
PICINIT:			
	mov al,0x11			;PIC �ʱ�ȭ ����         
	out 0x20, al
	dw 0x00eb, 0x00eb	   
	out 0xA0, al
	dw 0x00eb, 0x00eb

	mov al, 0x20		;������ PIC ���ͷ�Ʈ ����               
	out 0x21, al
	dw 0x00eb, 0x00eb
	mov al, 0x28		;�����̺� PIC ���ͷ�Ʈ ����         
	out 0xA1, al
	dw 0x00eb, 0x00eb

	mov al, 0x04		;������-�����̺� ���� ����          
	out 0x21, al		
	dw 0x00eb, 0x00eb
	mov al, 0x02		        
	out 0xA1, al		   
	dw 0x00eb, 0x00eb

	mov al, 0x01		;8086 ��� ���         
	out 0x21, al	
	dw 0x00eb, 0x00eb
	out 0xA1, al
	dw 0x00eb, 0x00eb

	mov al, 0xFF		;�����̺� PIC�� ��� ���ͷ�Ʈ ����          
	out 0xA1, al
	dw 0x00eb, 0x00eb
	mov al, 0xFB		;������ PIC�� IRQ 2���� ���� (�����̺� PIC���� ���)              
	out 0x21, al
	
LOADKERNEL:
	pop es
	
	jmp dword 0x18:0x10200

message: db 'Infinite Synthesis Kernel Start', 0

times 512 - ($ - $$) db 0x00