#############################################
#			Infinite Synthesis x64	  		#
#											#
# 파일 명: makefile							#
# 설명: Infinite Synthesis 빌드 용 makefile	#
# 최초 작성: 2019-01-22						#
#############################################
#		탭을 스페이스바로 입력하지 말 것.		#
#############################################

all: bootloader.img loadkernel.img Disk.img clean

###########################부트로더 빌드###########################
bootloader.img: ./Bootloader/bootloader.asm
	nasm -f bin -o ./Bootloader/bootloader.img ./Bootloader/bootloader.asm
	
loadkernel.img: ./Bootloader/loadkernel.asm
	nasm -f bin -o ./Bootloader/loadkernel.img ./Bootloader/loadkernel.asm
	
###########################32비트 커널 빌드###########################	



###########################64비트 커널 빌드###########################	



###########################운영체제 이미지 빌드###########################	
Disk.img: 
	cat ./Bootloader/bootloader.img ./Bootloader/loadkernel.img > Disk.img
	
clean:
	rm -rf ./Bootloader/bootloader.img ./Bootloader/loadkernel.img