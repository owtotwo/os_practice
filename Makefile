CC_CMD = gcc -Wall -g -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -fno-stack-protector -I. -c -m32 -o $@ $^

qemu: bootable.iso
	qemu bootable.iso -m 32

qemu-gdb: bootable.iso
	qemu bootable.iso -m 32 -s -S 

bootable.iso: iso/boot/kernel
	grub-mkrescue -o bootable.iso iso

iso/boot/kernel: link.ld start.o main.o scrn.o gdt.o idt.o isrs.o irq.o timer.o kb.o
	ld -g -m elf_i386 -T $^ -o $@

start.o: start.asm
	nasm -g -f elf $^ -o $@

main.o: main.c
	$(CC_CMD)

scrn.o: scrn.c
	$(CC_CMD)

gdt.o: gdt.c
	$(CC_CMD)

idt.o: idt.c
	$(CC_CMD)

isrs.o: isrs.c
	$(CC_CMD)

irq.o: irq.c
	$(CC_CMD)

timer.o: timer.c
	$(CC_CMD)

kb.o: kb.c
	$(CC_CMD)

clean:
	rm -f *.o
