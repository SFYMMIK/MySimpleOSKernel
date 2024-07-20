# MySimpleOSKernel

## Update 0.0.2 I Haven't still updated the readme i will do it later

MyKernel is a simple, not-yet-finished operating system kernel designed for educational purposes. It is intended to provide a basic understanding of kernel development, including interrupt handling, memory management, multitasking, system calls, and file system support.

## Features

- Basic bootloader
- Interrupt Descriptor Table (IDT)
- Basic Interrupt Service Routines (ISRs)
- Basic Paging and Memory Management
- Simple Multitasking
- Basic System Calls
- Placeholder for ext4 file system support

## Directory Structure

MySimpleOSKernel/
├── boot/
│ └── boot.asm
├── build/
├── idt.c
├── isr.c
├── kernel.c
├── paging.c
├── syscall.c
├── task.c
├── ext4.c
├── idt.h
├── isr.h
├── paging.h
├── syscall.h
├── task.h
├── ext4.h
└── linker.ld


## Prerequisites

To build and run this project, you will need the following tools:

- MSYS2 (Unix-like environment for Windows)
- GNU Make
- NASM (Netwide Assembler)
- i686-w64-mingw32 cross-compiler toolchain
- QEMU (for emulating the kernel)

## Setting Up The Development Environment

1. **Install MSYS2**

  - Download and install MSYS2 from the [official website](https://www.msys2.org/).

  - Update the package database and base packages:

   ```sh
   pacman -Syu
   ```
  - Close and reopen the MSYS2 terminal, then run:
    ```sh
    pacman -Su
    ```

2. **Install The Needed Packages

  ```sh
pacman -S base-devel mingw-w64-i686-toolchain mingw-w64-x86_64-toolchain
pacman -S nasm
```

3. **Verify The Toolchain Installation**
  - Open the "MSYS2 MinGW 32-bit" terminal and run:
  ```sh
i686-w64-mingw32-gcc --version
```

# Building The Kernel

1. **Go To The Directory Of The Kernel**
```sh
cd /home/example-user/MySimpleOSKernel/
```

2. **Build The Kernel**
```sh
make
```

# Running The Kernel
- Example Using QEMU:
  ```sh
  qemu-system-i386 -kernel build/kernel.bin
  ```
