#define IDT_PRESENT 0x80
#define IDT_INT_GATE 0x0E
#define IDT_TRAP_GATE 0x0F

#define saveStatus __asm__ __volatile__(\
	"pushfq;" \
	"push rax;"\
	"push rbx;"\
	"push rcx;"\
	"push rdx;" \
	"push rsp;" \
	"push rbp;" \
	"push rsi;" \
	"push rdi;"\
);

#define restoreStatus __asm__ __volatile__(\
	"pop rdi;"\
	"pop rsi;"\
	"pop rbp;"\
	"pop rsp;"\
	"pop rdx;"\
	"pop rcx;"\
	"pop rbx;"\
	"pop rax;"\
	"popfq;"\
	\
	"mov al, 0x20;"\
	"out 0x20, al;"\
	\
	"leave;"\
	"iretq;"\
);

//IDT 관련 구조체
typedef struct IDT{
	unsigned short lowerOffset;
	unsigned short selector;
	unsigned char ist;
	unsigned char typeAttr;
	unsigned short middleOffset;
	unsigned int higherOffset;
	unsigned int zerofill;
}__attribute__((packed)) IDT;

typedef struct IDTR{
	unsigned short limit;
	unsigned long base;
}__attribute__((packed)) IDTR;

//GDT 관련 구조체
typedef struct GDT{
	unsigned short lowerLimitAddress;
	unsigned short lowerBaseAddress;
	unsigned char middleBaseAddress;
	unsigned char accessByte;
	unsigned char higherLimitAndFlags;
	unsigned char higherBaseAddress;
}__attribute__((packed)) GDT;

typedef struct GDTR{
	unsigned short size;
	unsigned long offset;
}__attribute__((packed)) GDTR;

// 인터럽트 테이블 관련 함수
void initInterrupt();
void setIDTEntry(IDT *entry, void* isrAddress, unsigned short selector, unsigned char ist, unsigned char typeAndAttribute);
void isrDivideByZero();
void isrDummy();
void isrTimer();
void isrKeyboard();

// GDT 관련 함수
void initGDT();
void setGDTEntry(GDT *entry, unsigned int baseAddress, unsigned int limitAddress, unsigned char accessByte, unsigned char flags);