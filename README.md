# MySimpleOSKernel

## Current Version 0.0.7 BETA

## Working On: command to create/delete directiories and files, no more messy files in this repo, root and user password being protected, commands 'root' 'root -u' and 'cd' because they are still not finished, raspberry pi support/ARM support.

## Bugfixes: system commands fixed again.

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
- non-sys command execution
- '.rse' (Really Simple Executable)
- 'cd' for change directory made almost like on linux
- 'root' for just being root
- 'root -u' executing a command as root but without being root

## New updated instructions on how to compile (mainly for arch/arch-based linux distros)

## you need 
- i686-elf-gcc
- make
- glibc

## How to install i686-elf-gcc:
just type:
```sh
yay -S i686-elf-gcc
```
- But if you do not have yay installed here is a quick guide on how to install it:
```sh
sudo pacman -Sy base-devel git
```
```sh
git clone https://aur.archlinux.org/yay.git
```
```sh
cd ~/yay
```
```sh
makepkg -si
```
## Making the kernel an iso:

just type make:
```sh
make
```
and it should return the .iso file

## Using JustACCompiler

- To compile a C file using `JustACCompiler`, use the `compile` command followed by the filename:
    ```sh
    root@/>> compile example.c
    ```

    This will compile `example.c` and output `example.rse`.

# Remember that this project is licensed under the GNU GENERAL PUBLIC License
- so feel free to fork this project or just help me with building this kernel :)
