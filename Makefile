CFLAGS=-m32 -ffreestanding -O2 -Wall -Wextra
LDFLAGS=-m32 -T linker.ld -nostdlib

SOURCES = kernel.c idt.c isr.c terminal.c paging.c syscall.c task.c detector.c usb.c window_manager.c clock.c mouse.c filesystem.c
OBJECTS = $(SOURCES:.c=.o)

all: kernel.bin

kernel.bin: $(OBJECTS)
    i686-elf-gcc $(LDFLAGS) -o $@ $^

%.o: %.c
    i686-elf-gcc $(CFLAGS) -c -o $@ $<

clean:
    rm -f $(OBJECTS) kernel.bin
