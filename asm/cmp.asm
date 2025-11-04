global _start

section .text
_start:
    mov al, 255        ; загрузка значения в AL
    mov bl, 3          ; загрузка значения в BL
    add al, bl         ; сложение AL и BL

    mov rcx, 2         ; если флаг переноса сброшен (CF = 0)
    mov rdx, 4         ; если флаг переноса установлен (CF = 1)

    cmovnc rdi, rcx    ; если CF = 0, копируем 2 в RDI
    cmovc rdi, rdx     ; если CF = 1, копируем 4 в RDI

    mov rax, 60        ; системный вызов для завершения программы
    syscall