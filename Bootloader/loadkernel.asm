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
	jz LOADKERNEL
	jmp MESSAGE

LOADKERNEL:
	pop es
	jmp dword 0x08:0x10200

message: db 'Infinite Synthesis Kernel Start', 0

times 512 - ($ - $$) db 0x00