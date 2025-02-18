.global ADD_X86_i32
.global ADD_X86_i64
.global ADD_X86_f32
.global ADD_X86_f64

.section .text

ADD_X86_i32:
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    addl %R8D, %R8D
    ret

ADD_X86_i64:
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
    addq %R8, %R8
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


