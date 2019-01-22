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

jmp 0x07C0:START

START:
	mov ax, cs	; DS = CS
	mov ds, ax
	xor ax, ax
	
	mov si, 0xB800	                
	mov es, si		
	mov bx, 0x00	 
	mov cx, 80*25*2	                     

;화면 초기화
CLEAR:		              
	mov byte[es:bx], 0x00 
	inc bx
	loop CLEAR
	
;디스크 읽기
READ_INIT:			
	mov si, 0x1000	;0x1000:0000에 로드
	mov es, si
	mov bx, 0x0000	
	
READ:               			
	cmp word [TOTALSECTOR], 0	;if (TOTALSECTOR == 0)       
	je A20_ENABLE				;	jmp A20_ENABLE
	dec word [TOTALSECTOR]		       
	
    mov ah, 0x02                ;바이오스 인터럽트 설정
    mov al, 0x1                                
    mov ch, byte [TRACK]   		         
    mov cl, byte [SECTOR]   	         
    mov dh, byte [HEAD]   		
    mov dl, 0x80                ;플로피 디스크 (A:)               
    int 0x13                    
    jc READERROR              	

    add si, 0x0020      		;1 섹터 = 0x0020 (세그먼트 기준 주소)       
    mov es, si          		
	
	inc byte [SECTOR]			
	cmp byte [SECTOR], 19		;if(SECOTR != 19)
	jl READ						;	jmp READ             
								          
	xor byte [HEAD], 1			                
	mov byte [SECTOR], 1		          
    
	cmp byte [HEAD], 1			;if(HEAD == 1)             
	je READ   					;	jmp READ
								         
	inc byte [TRACK]			
	jmp READ                	                       
	
READERROR:			;읽기 실패시 더 이상 진행하지 않게 무한루프                        
	jmp $                
		 
;A20 GATE 활성화
A20_ENABLE:			    
	mov ax, 0x2401
	int 0x15
	jnc ENTRY

;바이오스 인터럽트 미 지원시 컨트롤 포트 사용
A20_FAIL:			            
	mov al, 0x02	
	out 0x92, al

;보호모드 진입
ENTRY:				        
	cli				;GDT 로드
	lgdt [GDTR]
	
	mov eax, cr0	;CR0.PE(0) 활성화
	or eax, 1
	mov cr0, eax
	
	jmp $+2			;파이프라인 유지를 위한 공백
	nop
	nop
	
	jmp dword 0x18:0x10000	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;GDT 영역;;;;;;;;;;;;;;;;;;;;;;;;;;;;

GDTR:	
	dw GDT_END - GDT - 1
	dd GDT+0x7C00

GDT:
	NULL:	;Null Descriptor
		dw 0
		dw 0
		db 0
		db 0
		db 0
		db 0	
	IA_32e_CODE:	;Kernel Code Descriptor
		dw 0xffff	
		dw 0x0000	
		db 0x00		
		db 0x9A		
		db 0xAF
		db 0x00 
	IA_32e_DATA:	;Kernel Data Descriptor
		dw 0xffff
		dw 0x0000
		db 0x00
		db 0x92
		db 0xAF
		db 0x00
	IA_32_CODE:	;Kernel Code Descriptor
		dw 0xffff	
		dw 0x0000	
		db 0x00		
		db 0x9A		
		db 0xCF
		db 0x00 
	IA_32_DATA:	;Kernel Data Descriptor
		dw 0xffff
		dw 0x0000
		db 0x00
		db 0x92
		db 0xCF
		db 0x00
	VIDEO:	;Video Segment Descriptor
		dw 0xffff
		dw 0x8000
		db 0x0B
		db 0x92
		db 0x40
		db 0x00
GDT_END:

;;;;;;;;;;;;;;;;;;;;;;;;;;;;변수 영역;;;;;;;;;;;;;;;;;;;;;;;;;;;;

TOTALSECTOR: dw 1024
SECTOR: dw 0x02
HEAD: db 0x00
TRACK: db 0x00 

;510 바이트까지 제로 필
times 510 - ($ - $$) db 0x00

;부트로더 시그니쳐
db 0x55
db 0xAA 
	

	

	
