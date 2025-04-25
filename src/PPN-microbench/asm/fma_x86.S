.global FMA_x86_f64_AVX
.global FMA_x86_f64_AVX2
.global FMA_x86_f64_AVX512

FMA_x86_f64_AVX:
    vbroadcastsd %xmm0, %ymm0
    vbroadcastsd %xmm1, %ymm1
    vbroadcastsd %xmm2, %ymm2

    vmovapd %ymm2, %ymm3
    vmovapd %ymm2, %ymm4
    vmovapd %ymm2, %ymm5
    vmovapd %ymm2, %ymm6
    vmovapd %ymm2, %ymm7
    vmovapd %ymm2, %ymm8
    vmovapd %ymm2, %ymm9
    vmovapd %ymm2, %ymm10
    vmovapd %ymm2, %ymm11
    vmovapd %ymm2, %ymm12
    vmovapd %ymm2, %ymm13
    vmovapd %ymm2, %ymm14

FMA_x86_f64_AVX_loop:
    vmulpd %ymm0, %ymm3, %ymm3
    vaddpd %ymm1, %ymm3, %ymm3

    vmulpd %ymm0, %ymm4, %ymm4
    vaddpd %ymm1, %ymm4, %ymm4

    vmulpd %ymm0, %ymm5, %ymm5
    vaddpd %ymm1, %ymm5, %ymm5

    vmulpd %ymm0, %ymm6, %ymm6
    vaddpd %ymm1, %ymm6, %ymm6

    vmulpd %ymm0, %ymm7, %ymm7
    vaddpd %ymm1, %ymm7, %ymm7

    vmulpd %ymm0, %ymm8, %ymm8
    vaddpd %ymm1, %ymm8, %ymm8

    vmulpd %ymm0, %ymm9, %ymm9
    vaddpd %ymm1, %ymm9, %ymm9

    vmulpd %ymm0, %ymm10, %ymm10
    vaddpd %ymm1, %ymm10, %ymm10

    vmulpd %ymm0, %ymm11, %ymm11
    vaddpd %ymm1, %ymm11, %ymm11

    vmulpd %ymm0, %ymm12, %ymm12
    vaddpd %ymm1, %ymm12, %ymm12

    vmulpd %ymm0, %ymm13, %ymm13
    vaddpd %ymm1, %ymm13, %ymm13

    vmulpd %ymm0, %ymm14, %ymm14
    vaddpd %ymm1, %ymm14, %ymm14

    decq %rdi
    jnz FMA_x86_f64_AVX_loop

    ret


FMA_x86_f64_AVX2:
    vbroadcastsd %xmm0, %ymm0  
    vbroadcastsd %xmm1, %ymm1  
    vbroadcastsd %xmm2, %ymm2  

    vmovapd %ymm2, %ymm3
    vmovapd %ymm2, %ymm4
    vmovapd %ymm2, %ymm5
    vmovapd %ymm2, %ymm6
    vmovapd %ymm2, %ymm7
    vmovapd %ymm2, %ymm8
    vmovapd %ymm2, %ymm9
    vmovapd %ymm2, %ymm10
    vmovapd %ymm2, %ymm11
    vmovapd %ymm2, %ymm12
    vmovapd %ymm2, %ymm13
    vmovapd %ymm2, %ymm14

FMA_x86_f64_AVX2_loop:
    vfmadd213pd %ymm1, %ymm0, %ymm3
    vfmadd213pd %ymm1, %ymm0, %ymm4
    vfmadd213pd %ymm1, %ymm0, %ymm5
    vfmadd213pd %ymm1, %ymm0, %ymm6

    vfmadd213pd %ymm1, %ymm0, %ymm7
    vfmadd213pd %ymm1, %ymm0, %ymm8
    vfmadd213pd %ymm1, %ymm0, %ymm9
    vfmadd213pd %ymm1, %ymm0, %ymm10

    vfmadd213pd %ymm1, %ymm0, %ymm11
    vfmadd213pd %ymm1, %ymm0, %ymm12
    vfmadd213pd %ymm1, %ymm0, %ymm13
    vfmadd213pd %ymm1, %ymm0, %ymm14

    decq %rdi
    jnz FMA_x86_f64_AVX2_loop

    ret


FMA_x86_f64_AVX512:
    vbroadcastsd %xmm0, %zmm0
    vbroadcastsd %xmm1, %zmm1
    vbroadcastsd %xmm2, %zmm2

    vmovapd %zmm2, %zmm3
    vmovapd %zmm2, %zmm4
    vmovapd %zmm2, %zmm5
    vmovapd %zmm2, %zmm6
    vmovapd %zmm2, %zmm7
    vmovapd %zmm2, %zmm8
    vmovapd %zmm2, %zmm9
    vmovapd %zmm2, %zmm10
    vmovapd %zmm2, %zmm11
    vmovapd %zmm2, %zmm12
    vmovapd %zmm2, %zmm13
    vmovapd %zmm2, %zmm14

FMA_x86_f64_AVX512_loop:
    vfmadd213pd %zmm1, %zmm0, %zmm3
    vfmadd213pd %zmm1, %zmm0, %zmm4
    vfmadd213pd %zmm1, %zmm0, %zmm5
    vfmadd213pd %zmm1, %zmm0, %zmm6
    vfmadd213pd %zmm1, %zmm0, %zmm7
    vfmadd213pd %zmm1, %zmm0, %zmm8
    vfmadd213pd %zmm1, %zmm0, %zmm9
    vfmadd213pd %zmm1, %zmm0, %zmm10
    vfmadd213pd %zmm1, %zmm0, %zmm11
    vfmadd213pd %zmm1, %zmm0, %zmm12
    vfmadd213pd %zmm1, %zmm0, %zmm13
    vfmadd213pd %zmm1, %zmm0, %zmm14

    decq %rdi
    jnz FMA_x86_f64_AVX512_loop

    ret