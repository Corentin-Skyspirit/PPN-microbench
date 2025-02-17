.global cpu_frequency_x86_64

cpu_frequency_x86_64:
    xor %rax, %rax 
    mov %rdi, %rcx
    shl $4, %rcx 

cpu_frequency_x86_64_loop_entry: 
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
    jl cpu_frequency_x86_64_loop_entry 

    ret
