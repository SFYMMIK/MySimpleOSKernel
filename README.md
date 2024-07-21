# MySimpleOSKernel

## Update 0.0.3

MyKernel is a simple, not-yet-finished operating system kernel designed for educational purposes. It is intended to provide a basic understanding of kernel development, including interrupt handling, memory management, multitasking, system calls, and file system support.

## Features

- Basic bootloader
- Interrupt Descriptor Table (IDT)
- Basic Interrupt Service Routines (ISRs)
- Basic Paging and Memory Management
- Simple Multitasking
- Basic System Calls
- Placeholder for ext4 file system support
- Basic shell with command execution
- User management with `useradd` command
- Simple in-memory filesystem with directory structure
- Basic window manager (S1) with window creation and closing
- Mouse support with a simple cursor

## Directory Structure

MySimpleOSKernel/
├── boot/
│ └── boot.asm
├── build/
├── kernel.c
├── idt.c
├── isr.c
├── paging.c
├── syscall.c
├── task.c
├── ext4.c
├── terminal.c
├── window_manager.c
├── mouse.c
├── filesystem.c
├── useradd.c
├── idt.h
├── isr.h
├── paging.h
├── syscall.h
├── task.h
├── ext4.h
├── terminal.h
├── window_manager.h
├── mouse.h
├── filesystem.h
├── useradd.h
└── linker.ld

## Prerequisites

To build and run this project, you will need the following tools:

- MSYS2 (Unix-like environment for Windows)
- GNU Make
- NASM (Netwide Assembler)
- i686-w64-mingw32 cross-compiler toolchain
- QEMU (for emulating the kernel)

## Setting Up The Development Environment (this probably works)

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

2. **Install The Needed Packages**
    ```sh
    pacman -S base-devel mingw-w64-i686-toolchain mingw-w64-x86_64-toolchain
    pacman -S nasm
    ```

3. **Verify The Toolchain Installation**
    - Open the "MSYS2 MinGW 32-bit" terminal and run:
    ```sh
    i686-w64-mingw32-gcc --version
    ```

## Building The Kernel

1. **Go To The Directory Of The Kernel**
    ```sh
    cd /home/example-user/MySimpleOSKernel/
    ```

2. **Build The Kernel**
    ```sh
    make
    ```

## Running The Kernel

- Example Using QEMU:
    ```sh
    qemu-system-i386 -kernel build/kernel.bin
    ```
