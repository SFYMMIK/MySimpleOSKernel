# MySimpleOSKernel

## Current Version 0.0.6 BETA

## Working On: command to create/delete directiories and files, no more messy files in this repo.

## Bugfixes: system commands fixed, compiler has its own command to compile as it should have had long before. 

# features
- basic bootloader (will change it in the future to GRUB or smth)
- window manager S1 which can just handle the windows and has basic functions
- the kernel itself
- its own simple compiler
- detection of keyboards and mouse
- detection of clicking types
- working shell and commands (probably)
- simple directories (/ /user/ and /prog/ and thats it)
- mouse cursor support with a simple arrow cursor
- basic interrupt descriptor table (IDT)
- basic interrupt service routines (ISRs)
- basic paging and memory managment
- simple (i thinks its still in-memory) filesystem
- user managment with the 'useradd' command
- basic shell with command execution
- basic system calls
- simple multitasking
- detection of gui
- (probably) working filesystem on ext4
- (probably) working clock (with gui or cli)
- 'te' short for 'text editor' is like nano but on this kernel

## Just some older instructions on how to compile the kernel and use JustACCompiler

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

## Using JustACCompiler

- To compile a C file using `JustACCompiler`, use the `compile` command followed by the filename:
    ```sh
    root@/>> compile example.c
    ```

    This will compile `example.c` and output `example.c.out`.

# Remember that this project is licensed under the GNU GENERAL PUBLIC License
- so feel free to fork this project or just help me with building this kernel :)