#############################################
#			Infinite Synthesis x64	  		#
#											#
# 파일 명: ./boot/makefile						#
# 설명: Infinite Synthesis 빌드 용 makefile		#
# 최초 작성: 2020-04-02							#
#############################################
#			탭을 스페이스바로 입력하지 말 것.			#
#############################################

NASM = nasm -f bin
all: bootloader.img loadkernel.img boot.bin clean

bootloader.img: bootloader.asm
	$(NASM) $^ -o $@
	
loadkernel.img: loadkernel.asm
	$(NASM) $^ -o $@
	
boot.bin: bootloader.img loadkernel.img
	cat $^ > $@
	
.PHONY: clean

clean:
	rm -f *.img