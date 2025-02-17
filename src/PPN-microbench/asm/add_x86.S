.global ADD_X86_i32
.global ADD_X86_i64
.global ADD_X86_f32
.global ADD_X86_f64

.section .text

ADD_X86_i32:
    pushq %rax

    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax
    addl %eax, %eax

    popq %rax
    ret

ADD_X86_i64:
    pushq %rax

    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax
    addq %rax, %rax

    popq %rax
    ret

ADD_X86_f32:
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0
    addss %xmm0, %xmm0

    ret

ADD_X86_f64:
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0
    addsd %xmm0, %xmm0

    ret


