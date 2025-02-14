.global cpu_frequency_x86_64

cpu_frequency_x86_64:
    xor %rax, %rax 
    mov %rdi, %rcx
    shl $4, %rcx 

1: 
    add $1, %rax
    add $1, %rax
    add $1, %rax
    add $1, %rax

    add $1, %rax
    add $1, %rax
    add $1, %rax
    add $1, %rax

    add $1, %rax
    add $1, %rax
    add $1, %rax
    add $1, %rax

    add $1, %rax
    add $1, %rax
    add $1, %rax
    add $1, %rax

    cmp %rcx, %rax
    jl 1b  

    ret