# Define the cross-compiler
CC=i686-elf-gcc
AS=i686-elf-as
LD=i686-elf-ld

# Directories
BUILD=build
SRC=src
ISO=iso

# Kernel source files
KERNEL_SRC=$(SRC)/kernel.c
KERNEL_OBJ=$(BUILD)/kernel.o

# Kernel binary
KERNEL_BIN=$(BUILD)/kernel.bin

# ISO file
ISO_FILE=MySimpleOS.iso

# Flags
CFLAGS=-ffreestanding -O2 -Wall -Wextra
LDFLAGS=-T linker.ld -ffreestanding -O2 -nostdlib

# Default target
all: iso

# Compile the kernel
$(KERNEL_OBJ): $(KERNEL_SRC)
	@mkdir -p $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

# Link the kernel
$(KERNEL_BIN): $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^

# Create ISO directory structure
iso_dir:
	mkdir -p $(ISO)/boot/grub

# Copy kernel and create GRUB config
copy_files: $(KERNEL_BIN) iso_dir
	cp $(KERNEL_BIN) $(ISO)/boot/kernel.bin
	echo 'menuentry "My Simple OS" { multiboot /boot/kernel.bin boot }' > $(ISO)/boot/grub/grub.cfg

# Create ISO image
iso: copy_files
	grub-mkrescue -o $(ISO_FILE) $(ISO)

# Clean build files
clean:
	rm -rf $(BUILD) $(ISO) $(ISO_FILE)

.PHONY: all clean iso_dir copy_files iso
