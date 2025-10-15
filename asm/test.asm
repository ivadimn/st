global _start

section .text

_start:
    ;write your code here
    mov rax, 60
    mov rdi, 42
    syscall