#############################################
#			Infinite Synthesis x64	  		#
#											#
# ���� ��: makefile							#
# ����: Infinite Synthesis ���� �� makefile	#
# ���� �ۼ�: 2019-01-22						#
#############################################
#		���� �����̽��ٷ� �Է����� �� ��.		#
#############################################

all: bootloader.img loadkernel.img Disk.img clean

###########################��Ʈ�δ� ����###########################
bootloader.img: ./Bootloader/bootloader.asm
	nasm -f bin -o ./Bootloader/bootloader.img ./Bootloader/bootloader.asm
	
loadkernel.img: ./Bootloader/loadkernel.asm
	nasm -f bin -o ./Bootloader/loadkernel.img ./Bootloader/loadkernel.asm
	
###########################32��Ʈ Ŀ�� ����###########################	



###########################64��Ʈ Ŀ�� ����###########################	



###########################�ü�� �̹��� ����###########################	
Disk.img: 
	cat ./Bootloader/bootloader.img ./Bootloader/loadkernel.img > Disk.img
	
clean:
	rm -rf ./Bootloader/bootloader.img ./Bootloader/loadkernel.img