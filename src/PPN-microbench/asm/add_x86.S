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
    addl %R9D, %R9D
    addl %R10D, %R10D
    addl %R11D, %R11D
    addl %R12D, %R12D
    addl %R13D, %R13D
    addl %R14D, %R14D
    addl %R15D, %R15D
    addl %R8D, %R8D
    addl %R9D, %R9D
    addl %R10D, %R10D
    addl %R11D, %R11D
    addl %R12D, %R12D
    addl %R13D, %R13D
    addl %R14D, %R14D
    addl %R15D, %R15D

    subq $1, %rdi
    jg loop1
    ret

ADD_X86_i64:
loop2:
    addq %R8, %R8
    addq %R9, %R9
    addq %R10, %R10
    addq %R11, %R11
    addq %R12, %R12
    addq %R13, %R13
    addq %R14, %R14
    addq %R15, %R15
    addq %R8, %R8
    addq %R9, %R9
    addq %R10, %R10
    addq %R11, %R11
    addq %R12, %R12
    addq %R13, %R13
    addq %R14, %R14
    addq %R15, %R15

    subq $1, %rdi
    jg loop2
    ret

ADD_X86_f32:
loop3:
    addss %xmm0, %xmm0
    addss %xmm1, %xmm1
    addss %xmm2, %xmm2
    addss %xmm3, %xmm3
    addss %xmm4, %xmm4
    addss %xmm5, %xmm5
    addss %xmm6, %xmm6
    addss %xmm7, %xmm7
    addss %xmm8, %xmm8
    addss %xmm9, %xmm9
    addss %xmm10, %xmm10
    addss %xmm10, %xmm10
    addss %xmm11, %xmm11
    addss %xmm12, %xmm12
    addss %xmm13, %xmm13
    addss %xmm14, %xmm14

    subq $1, %rdi
    jg loop3
    ret

ADD_X86_f64:
loop4:
    addsd %xmm0, %xmm0
    addsd %xmm1, %xmm1
    addsd %xmm2, %xmm2
    addsd %xmm3, %xmm3
    addsd %xmm4, %xmm4
    addsd %xmm5, %xmm5
    addsd %xmm6, %xmm6
    addsd %xmm7, %xmm7
    addsd %xmm8, %xmm8
    addsd %xmm9, %xmm9
    addsd %xmm10, %xmm10
    addsd %xmm10, %xmm10
    addsd %xmm11, %xmm11
    addsd %xmm12, %xmm12
    addsd %xmm13, %xmm13
    addsd %xmm14, %xmm14

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
    paddq %xmm1, %xmm1
    paddq %xmm2, %xmm2
    paddq %xmm3, %xmm3
    paddq %xmm4, %xmm4
    paddq %xmm5, %xmm5
    paddq %xmm6, %xmm6
    paddq %xmm7, %xmm7
    paddq %xmm8, %xmm8
    paddq %xmm9, %xmm9
    paddq %xmm10, %xmm10
    paddq %xmm11, %xmm11
    paddq %xmm12, %xmm12
    paddq %xmm13, %xmm13
    paddq %xmm14, %xmm14
    paddq %xmm15, %xmm15

    subq $1, %rdi
    jg loop5
    ret

ADD_X86_f64_SSE:
loop6:
    addpd %xmm0, %xmm0
    addpd %xmm1, %xmm1
    addpd %xmm2, %xmm2
    addpd %xmm3, %xmm3
    addpd %xmm4, %xmm4
    addpd %xmm5, %xmm5
    addpd %xmm6, %xmm6
    addpd %xmm7, %xmm7
    addpd %xmm8, %xmm8
    addpd %xmm9, %xmm9
    addpd %xmm10, %xmm10
    addpd %xmm11, %xmm11
    addpd %xmm12, %xmm12
    addpd %xmm13, %xmm13
    addpd %xmm14, %xmm14
    addpd %xmm15, %xmm15

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
    vaddpd %ymm1, %ymm1, %ymm1
    vaddpd %ymm2, %ymm2, %ymm2
    vaddpd %ymm3, %ymm3, %ymm3
    vaddpd %ymm4, %ymm4, %ymm4
    vaddpd %ymm5, %ymm5, %ymm5
    vaddpd %ymm6, %ymm6, %ymm6
    vaddpd %ymm7, %ymm7, %ymm7
    vaddpd %ymm8, %ymm8, %ymm8
    vaddpd %ymm9, %ymm9, %ymm9
    vaddpd %ymm10, %ymm10, %ymm10
    vaddpd %ymm11, %ymm11, %ymm11
    vaddpd %ymm12, %ymm12, %ymm12
    vaddpd %ymm13, %ymm13, %ymm13
    vaddpd %ymm14, %ymm14, %ymm14
    vaddpd %ymm15, %ymm15, %ymm15

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
    vpaddq %ymm1, %ymm1, %ymm1
    vpaddq %ymm2, %ymm2, %ymm2
    vpaddq %ymm3, %ymm3, %ymm3
    vpaddq %ymm4, %ymm4, %ymm4
    vpaddq %ymm5, %ymm5, %ymm5
    vpaddq %ymm6, %ymm6, %ymm6
    vpaddq %ymm7, %ymm7, %ymm7
    vpaddq %ymm8, %ymm8, %ymm8
    vpaddq %ymm9, %ymm9, %ymm9
    vpaddq %ymm10, %ymm10, %ymm10
    vpaddq %ymm11, %ymm11, %ymm11
    vpaddq %ymm12, %ymm12, %ymm12
    vpaddq %ymm13, %ymm13, %ymm13
    vpaddq %ymm14, %ymm14, %ymm14
    vpaddq %ymm15, %ymm15, %ymm15

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
    vpaddq %Zmm0, %Zmm0, %Zmm0
    vpaddq %Zmm1, %Zmm1, %Zmm1
    vpaddq %Zmm2, %Zmm2, %Zmm2
    vpaddq %Zmm3, %Zmm3, %Zmm3
    vpaddq %Zmm4, %Zmm4, %Zmm4
    vpaddq %Zmm5, %Zmm5, %Zmm5
    vpaddq %Zmm6, %Zmm6, %Zmm6
    vpaddq %Zmm7, %Zmm7, %Zmm7
    vpaddq %Zmm8, %Zmm8, %Zmm8
    vpaddq %Zmm9, %Zmm9, %Zmm9
    vpaddq %Zmm10, %Zmm10, %Zmm10
    vpaddq %Zmm11, %Zmm11, %Zmm11
    vpaddq %Zmm12, %Zmm12, %Zmm12
    vpaddq %Zmm13, %Zmm13, %Zmm13
    vpaddq %Zmm14, %Zmm14, %Zmm14
    vpaddq %Zmm15, %Zmm15, %Zmm15

    subq $1, %rdi
    jg loop9
    ret

ADD_X86_f64_AVX512:
loop10:
    vaddpd %Zmm0, %Zmm0, %Zmm0
    vaddpd %Zmm1, %Zmm1, %Zmm1
    vaddpd %Zmm2, %Zmm2, %Zmm2
    vaddpd %Zmm3, %Zmm3, %Zmm3
    vaddpd %Zmm4, %Zmm4, %Zmm4
    vaddpd %Zmm5, %Zmm5, %Zmm5
    vaddpd %Zmm6, %Zmm6, %Zmm6
    vaddpd %Zmm7, %Zmm7, %Zmm7
    vaddpd %Zmm8, %Zmm8, %Zmm8
    vaddpd %Zmm9, %Zmm9, %Zmm9
    vaddpd %Zmm10, %Zmm10, %Zmm10
    vaddpd %Zmm11, %Zmm11, %Zmm11
    vaddpd %Zmm12, %Zmm12, %Zmm12
    vaddpd %Zmm13, %Zmm13, %Zmm13
    vaddpd %Zmm14, %Zmm14, %Zmm14
    vaddpd %Zmm15, %Zmm15, %Zmm15

    subq $1, %rdi
    jg loop10
    ret