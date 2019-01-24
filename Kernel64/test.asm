[ORG 0x200000]
[BITS 64]

section .text

START:
	mov ax, 0x10
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov ds, ax
	
	mov rsp, 0x6FFFE
	mov rbp, 0x6FFFE
		
	