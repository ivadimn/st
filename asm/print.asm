bits 64
global _start

section .data
text_message: db "Welcom to ASM!", 0xA

section .text
_start:
    mov rax, 1      ; функция write
    mov rdi, 1      ; в стандартный поток stdout
    mov rsi, text_message
    mov rdx, 17     ; длина строки в байтах
    syscall

    mov rax, 60     ; функция exit
    xor rdi, rdi    ; кодвозврата 0
    syscall 