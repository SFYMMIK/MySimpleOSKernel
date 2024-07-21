# Cross-compiler tools
CC = i686-elf-gcc
LD = i686-elf-ld
AS = i686-elf-as
GDB = i686-elf-gdb

CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS = -ffreestanding -O2 -nostdlib

# Kernel objects
KERNEL_OBJS = kernel.o terminal.o isr.o idt.o paging.o syscall.o task.o ext4.o window_manager.o mouse.o filesystem.o

# Programs
PROG_OBJS = useradd.o

# Final kernel binary
KERNEL_BIN = mykernel.bin

.PHONY: all clean

all: $(KERNEL_BIN)

$(KERNEL_BIN): $(KERNEL_OBJS) $(PROG_OBJS)
	$(LD) -T linker.ld -o $(KERNEL_BIN) $(KERNEL_OBJS) $(PROG_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(KERNEL_OBJS) $(PROG_OBJS) $(KERNEL_BIN)
