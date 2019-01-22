#############################################
#			Infinite Synthesis x64	  		#
#											#
# ���� ��: makefile							#
# ����: Infinite Synthesis ���� �� makefile	#
# ���� �ۼ�: 2019-01-22						#
#############################################
#		���� �����̽��ٷ� �Է����� �� ��.		#
#############################################

all: bootloader.img Disk.img clean

bootloader.img: ./Bootloader/bootloader.asm
	nasm -f bin -o ./Bootloader/bootloader.img ./Bootloader/bootloader.asm
	
Disk.img: 
	cat ./Bootloader/bootloader.img > Disk.img
	
clean:
	rm -rf ./Bootloader/bootloader.img