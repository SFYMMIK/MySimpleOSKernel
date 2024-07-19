section .text
global switch_task_asm

switch_task_asm:
    cli
    push ebp
    push esp
    mov ebp, esp
    mov esp, [esp + 8]
    pop esp
    pop ebp
    sti
    ret
