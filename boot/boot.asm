section .text
global isr0

isr0:
    cli
    push 0
    push 0x00
    jmp isr_common_stub

isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    call isr_handler
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    sti
    iret
