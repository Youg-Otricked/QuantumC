.global _start
.intel_syntax
.section .text
#72 101 108 108 111 44 32 87 111 114 108 100 33
_start:
#add char
    mov %eax, 4
    mov %ebx, 1
    lea %ecx, [message]
    mov %edx, 14
    int 0x80

    #exit program
    mov %eax, 1
    mov %ebx, 0

    int 0x80

.section .data
    message:
    .ascii "Hello, World!\n"