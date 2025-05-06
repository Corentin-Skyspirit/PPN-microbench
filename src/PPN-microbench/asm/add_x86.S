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
    vaddss %xmm0, %xmm0, %xmm1
    vaddss %xmm0, %xmm0, %xmm2
    vaddss %xmm0, %xmm0, %xmm3
    vaddss %xmm0, %xmm0, %xmm4
    vaddss %xmm0, %xmm0, %xmm5
    vaddss %xmm0, %xmm0, %xmm6
    vaddss %xmm0, %xmm0, %xmm7
    vaddss %xmm0, %xmm0, %xmm8
    vaddss %xmm0, %xmm0, %xmm9
    vaddss %xmm0, %xmm0, %xmm10
    vaddss %xmm0, %xmm0, %xmm11
    vaddss %xmm0, %xmm0, %xmm12
    vaddss %xmm0, %xmm0, %xmm13
    vaddss %xmm0, %xmm0, %xmm14
    vaddss %xmm0, %xmm0, %xmm15
    vaddss %xmm0, %xmm0, %xmm1

    subq $1, %rdi
    jg loop3
    ret

ADD_X86_f64:
loop4:
    vaddsd %xmm0, %xmm0, %xmm1
    vaddsd %xmm0, %xmm0, %xmm2
    vaddsd %xmm0, %xmm0, %xmm3
    vaddsd %xmm0, %xmm0, %xmm4
    vaddsd %xmm0, %xmm0, %xmm5
    vaddsd %xmm0, %xmm0, %xmm6
    vaddsd %xmm0, %xmm0, %xmm7
    vaddsd %xmm0, %xmm0, %xmm8
    vaddsd %xmm0, %xmm0, %xmm9
    vaddsd %xmm0, %xmm0, %xmm10
    vaddsd %xmm0, %xmm0, %xmm11
    vaddsd %xmm0, %xmm0, %xmm12
    vaddsd %xmm0, %xmm0, %xmm13
    vaddsd %xmm0, %xmm0, %xmm14
    vaddsd %xmm0, %xmm0, %xmm15
    vaddsd %xmm0, %xmm0, %xmm1

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
    paddq %xmm0, %xmm1
    paddq %xmm0, %xmm2
    paddq %xmm0, %xmm3
    paddq %xmm0, %xmm4
    paddq %xmm0, %xmm5
    paddq %xmm0, %xmm6
    paddq %xmm0, %xmm7
    paddq %xmm0, %xmm8
    paddq %xmm0, %xmm9
    paddq %xmm0, %xmm10
    paddq %xmm0, %xmm11
    paddq %xmm0, %xmm12
    paddq %xmm0, %xmm13
    paddq %xmm0, %xmm14
    paddq %xmm0, %xmm15
    paddq %xmm0, %xmm1

    subq $1, %rdi
    jg loop5
    ret

ADD_X86_f64_SSE:
loop6:
    addpd %xmm0, %xmm1
    addpd %xmm0, %xmm2
    addpd %xmm0, %xmm3
    addpd %xmm0, %xmm4
    addpd %xmm0, %xmm5
    addpd %xmm0, %xmm6
    addpd %xmm0, %xmm7
    addpd %xmm0, %xmm8
    addpd %xmm0, %xmm9
    addpd %xmm0, %xmm10
    addpd %xmm0, %xmm11
    addpd %xmm0, %xmm12
    addpd %xmm0, %xmm13
    addpd %xmm0, %xmm14
    addpd %xmm0, %xmm15
    addpd %xmm0, %xmm1

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
    vaddpd %ymm0, %ymm0, %ymm1
    vaddpd %ymm0, %ymm0, %ymm2
    vaddpd %ymm0, %ymm0, %ymm3
    vaddpd %ymm0, %ymm0, %ymm4
    vaddpd %ymm0, %ymm0, %ymm5
    vaddpd %ymm0, %ymm0, %ymm6
    vaddpd %ymm0, %ymm0, %ymm7
    vaddpd %ymm0, %ymm0, %ymm8
    vaddpd %ymm0, %ymm0, %ymm9
    vaddpd %ymm0, %ymm0, %ymm10
    vaddpd %ymm0, %ymm0, %ymm11
    vaddpd %ymm0, %ymm0, %ymm12
    vaddpd %ymm0, %ymm0, %ymm13
    vaddpd %ymm0, %ymm0, %ymm14
    vaddpd %ymm0, %ymm0, %ymm15
    vaddpd %ymm0, %ymm0, %ymm1

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
    vpaddq %ymm0, %ymm0, %ymm1
    vpaddq %ymm0, %ymm0, %ymm2
    vpaddq %ymm0, %ymm0, %ymm3
    vpaddq %ymm0, %ymm0, %ymm4
    vpaddq %ymm0, %ymm0, %ymm5
    vpaddq %ymm0, %ymm0, %ymm6
    vpaddq %ymm0, %ymm0, %ymm7
    vpaddq %ymm0, %ymm0, %ymm8
    vpaddq %ymm0, %ymm0, %ymm9
    vpaddq %ymm0, %ymm0, %ymm10
    vpaddq %ymm0, %ymm0, %ymm11
    vpaddq %ymm0, %ymm0, %ymm12
    vpaddq %ymm0, %ymm0, %ymm13
    vpaddq %ymm0, %ymm0, %ymm14
    vpaddq %ymm0, %ymm0, %ymm15
    vpaddq %ymm0, %ymm0, %ymm1

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
    vpaddq %zmm0, %zmm0, %zmm1
    vpaddq %zmm0, %zmm0, %zmm2
    vpaddq %zmm0, %zmm0, %zmm3
    vpaddq %zmm0, %zmm0, %zmm4
    vpaddq %zmm0, %zmm0, %zmm5
    vpaddq %zmm0, %zmm0, %zmm6
    vpaddq %zmm0, %zmm0, %zmm7
    vpaddq %zmm0, %zmm0, %zmm8
    vpaddq %zmm0, %zmm0, %zmm9
    vpaddq %zmm0, %zmm0, %zmm10
    vpaddq %zmm0, %zmm0, %zmm11
    vpaddq %zmm0, %zmm0, %zmm12
    vpaddq %zmm0, %zmm0, %zmm13
    vpaddq %zmm0, %zmm0, %zmm14
    vpaddq %zmm0, %zmm0, %zmm15
    vpaddq %zmm0, %zmm0, %zmm1

    subq $1, %rdi
    jg loop9
    ret

ADD_X86_f64_AVX512:
loop10:
    vaddpd %zmm0, %zmm0, %zmm1
    vaddpd %zmm0, %zmm0, %zmm2
    vaddpd %zmm0, %zmm0, %zmm3
    vaddpd %zmm0, %zmm0, %zmm4
    vaddpd %zmm0, %zmm0, %zmm5
    vaddpd %zmm0, %zmm0, %zmm6
    vaddpd %zmm0, %zmm0, %zmm7
    vaddpd %zmm0, %zmm0, %zmm8
    vaddpd %zmm0, %zmm0, %zmm9
    vaddpd %zmm0, %zmm0, %zmm10
    vaddpd %zmm0, %zmm0, %zmm11
    vaddpd %zmm0, %zmm0, %zmm12
    vaddpd %zmm0, %zmm0, %zmm13
    vaddpd %zmm0, %zmm0, %zmm14
    vaddpd %zmm0, %zmm0, %zmm15
    vaddpd %zmm0, %zmm0, %zmm1

    subq $1, %rdi
    jg loop10
    ret