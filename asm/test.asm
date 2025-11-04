global _start

section .text

_start:
    mov rsi, 0x0F
    test rsi, 0x01     ; проверяем младший бит

    jne bit_set        ; если бит установлен (не ноль)
    mov rdi, 0         ; бит не установлен
    jmp finish

bit_set:
    mov rdi, 1         ; бит установлен

finish:
    mov rax, 60
    syscall