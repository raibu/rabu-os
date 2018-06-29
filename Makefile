PREFIX=i386-elf-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld 
ASM=nasm
EXTC=$(wildcard drivers/*.c cpu/*.c libc/*.c)


run: image 
	qemu-system-x86_64 -fda out/os-image.bin  

debug: image link
	qemu-system-i386 -s -S -fda out/os-image.bin &> /dev/null & i386-elf-gdb -ex "target remote localhost:1234" -ex "symbol-file out/kernel.elf"



bootloader:
	$(ASM) -f bin  -I boot/ boot/boot.asm -o out/boot.o -O2

interrupts:
	$(ASM) -f elf  cpu/interrupt.asm -o out/interrupt.o -O2

kentry:
	$(ASM) boot/kentry.asm -f elf -o out/kentry.o -O2

kmain: interrupts
	$(CC) -g -ffreestanding -c kernel/kmain.c -o out/kmain.o -std=c99 -O2
	$(foreach file, $(EXTC), $(CC) -g -ffreestanding -nostdlib -nostdinc  -fno-builtin-functions -ansi -c $(file) -o ${file:.c=.o} -std=c99 -O2;)
	

link: kmain kentry
	mkdir -p out 
	$(LD) -o out/kernel.elf -Ttext 0x1000 out/kentry.o  out/kmain.o ${EXTC:.c=.o} out/interrupt.o

linkbin: kmain kentry
	mkdir -p out 
	$(LD) -o out/kernel.bin -Ttext 0x1000 out/kentry.o  out/kmain.o ${EXTC:.c=.o} out/interrupt.o --oformat binary

image: bootloader linkbin
	cat out/boot.o out/kernel.bin > out/os-image.bin

clean:
	rm -f *.o */*.o out/*


open:
	subl3 */*.{asm,c,h} -n -a
