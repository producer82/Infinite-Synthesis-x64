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

	mov ebx, 0			; 매세지 출력 준비
	lea esi, [message]
	push es				; es에 들어있는 데이터세그 값을 저장함
	mov ax, 0x28 ; 비디오 세그먼트 값 넣고
	mov es, ax
	mov ah, 0x0E

MESSAGE:
	lodsb
	mov byte [es:ebx], al	;비디오 메모리:EDI에 al 넣고
	inc ebx					;비디오 메모리 오프셋 늘리고
	mov byte [es:ebx], ah	;속성값 넣고
	inc ebx					;edi 늘리고 
	cmp al, 0				;0인지 확인하고
	jz PICINIT
	jmp MESSAGE
	
PICINIT:			
	mov al,0x11			;PIC 초기화 시작         
	out 0x20, al
	dw 0x00eb, 0x00eb	   
	out 0xA0, al
	dw 0x00eb, 0x00eb

	mov al, 0x20		;마스터 PIC 인터럽트 시작               
	out 0x21, al
	dw 0x00eb, 0x00eb
	mov al, 0x28		;슬레이브 PIC 인터럽트 시작         
	out 0xA1, al
	dw 0x00eb, 0x00eb

	mov al, 0x04		;마스터-슬레이브 연결 설정          
	out 0x21, al		
	dw 0x00eb, 0x00eb
	mov al, 0x02		        
	out 0xA1, al		   
	dw 0x00eb, 0x00eb

	mov al, 0x01		;8086 모드 사용         
	out 0x21, al	
	dw 0x00eb, 0x00eb
	out 0xA1, al
	dw 0x00eb, 0x00eb

	mov al, 0xFF		;슬레이브 PIC의 모든 인터럽트 중지          
	out 0xA1, al
	dw 0x00eb, 0x00eb
	mov al, 0xFB		;마스터 PIC의 IRQ 2번만 개방 (슬레이브 PIC로의 통로)              
	out 0x21, al
	
LOADKERNEL:
	pop es
	
	jmp dword 0x18:0x10200

message: db 'Infinite Synthesis Kernel Start', 0

times 512 - ($ - $$) db 0x00