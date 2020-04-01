#############################################
#			Infinite Synthesis x64	  		#
#											#
# 파일 명: ./boot/makefile						#
# 설명: Infinite Synthesis 빌드 용 makefile		#
# 최초 작성: 2019-01-22							#
#############################################
#			탭을 스페이스바로 입력하지 말 것.			#
#############################################

NASM = nasm -f bin
IMGS = bootloader.img loadkernel.img

$(TARGET): $(IMGS)
	$(NASM) $^ -o $@
	
bootloader.img: bootloader.asm
	
loadkernel.img: loadkernel.asm
	
boot.bin: ./boot/bootloader.img ./boot/loadkernel.img
	cat $^ > $@
	
.PHONY: clean

clean:
	rm -f *.img