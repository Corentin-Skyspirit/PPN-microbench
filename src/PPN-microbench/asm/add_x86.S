.global ADD_X86_i32
.global ADD_X86_i64
.global ADD_X86_f32
.global ADD_X86_f64

.global ADD_X86_i64_SSE
.global ADD_X86_f64_SSE

.global ADD_X86_i64_AVX
.global ADD_X86_f64_AVX

.global ADD_X86_i64_AVX512
.global ADD_X86_f64_AVX512

.section .text

#
#
# SCALAR
#
#

ADD_X86_i32:
loop1:
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

    subq $1, %rdi
    jg loop1
    ret

ADD_X86_i64:
loop2:
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

    subq $1, %rdi
    jg loop2
    ret

ADD_X86_f32:
loop3:
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

    subq $1, %rdi
    jg loop3
    ret

ADD_X86_f64:
loop4:
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

    subq $1, %rdi
    jg loop4
    ret

#
#
# SSE
#
#

ADD_X86_i64_SSE:
loop5:
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0
    paddq %xmm0, %xmm0

    subq $1, %rdi
    jg loop5
    ret

ADD_X86_f64_SSE:
loop6:
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0
    addpd %xmm0, %xmm0

    subq $1, %rdi
    jg loop6
    ret

#
#
# AVX
#
#

ADD_X86_f64_AVX:
loop7:
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0
    vaddpd %ymm0, %ymm0, %ymm0

    subq $1, %rdi
    jg loop7
    ret

#
#
# AVX2
#
#

ADD_X86_i64_AVX:
loop8:
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0
    vpaddq %ymm0, %ymm0, %ymm0

    subq $1, %rdi
    jg loop8
    ret

#
#
# AVX512
#
#

ADD_X86_i64_AVX512:
loop9:
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0
    vpaddq %zmm0, %zmm0, %zmm0

    subq $1, %rdi
    jg loop9
    ret

ADD_X86_f64_AVX512:
loop10:
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0
    vaddpd %zmm0, %zmm0, %zmm0

    subq $1, %rdi
    jg loop10
    ret