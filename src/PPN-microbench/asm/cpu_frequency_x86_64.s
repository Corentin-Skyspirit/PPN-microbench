.global cpu_frequency_x86_64

cpu_frequency_x86_64:
    xor rax, rax
    mov rcx, rdi
    shl rcx, 4

start:
    add rax, 1
    add rax, 1
    add rax, 1
    add rax, 1

    add rax, 1
    add rax, 1
    add rax, 1
    add rax, 1

    add rax, 1
    add rax, 1
    add rax, 1
    add rax, 1

    add rax, 1
    add rax, 1
    add rax, 1
    add rax, 1

    cmp rax, rcx
    jl start

    ret