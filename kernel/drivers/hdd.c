#include "drivers.h"

void readSector(){
	
}

void writeSector(){
	
}

char readStatusRegister(){
	unsigned char statusRegister = 0;
	
	__asm__ __volatile__(
		"in ax, 0x1F7;"
		"mov %0, ax"::"=r"(statusRegister);
	);
	
	return statusRegister;
}

void cacheFlush(){
	__asm__ __volatile__(
		"out 0x1F7, 0xE7;"
	);
}

char isErr(){
	if(statusRegister() & 0x1) {
		return 1;
	}
	else {
		return 0;
	}
}

char isDrq(){
	if((statusRegister() >> 3) & 0x1) {
		return 1;
	}
	else {
		return 0;
	}
}

char isRdy(){
	if((statusRegister() >> 6) & 0x1) {
		return 1;
	}
	else {
		return 0;
	}
}

char isBsy(){
	if((statusRegister() >> 7) & 0x1) {
		return 1;
	}
	else {
		return 0;
	}
}