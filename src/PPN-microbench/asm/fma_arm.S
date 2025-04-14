.global FMA_ARM_f64_NEON

FMA_ARM_f64_NEON:
    fmov    x1, d0
    dup     v0.2d, x1

    fmov    x2, d1
    dup     v1.2d, x2

    fmov    x3, d2
    dup     v2.2d, x3

    mov     v3.16b, v2.16b
    mov     v4.16b, v2.16b
    mov     v5.16b, v2.16b
    mov     v6.16b, v2.16b
    mov     v7.16b, v2.16b
    mov     v8.16b, v2.16b
    mov     v9.16b, v2.16b
    mov     v10.16b, v2.16b
    mov     v11.16b, v2.16b
    mov     v12.16b, v2.16b
    mov     v13.16b, v2.16b
    mov     v14.16b, v2.16b

FMA_ARM_f64_NEON_loop:
    fmul    v3.2d, v3.2d, v0.2d
    fadd    v3.2d, v3.2d, v1.2d

    fmul    v4.2d, v4.2d, v0.2d
    fadd    v4.2d, v4.2d, v1.2d

    fmul    v5.2d, v5.2d, v0.2d
    fadd    v5.2d, v5.2d, v1.2d

    fmul    v6.2d, v6.2d, v0.2d
    fadd    v6.2d, v6.2d, v1.2d

    fmul    v7.2d, v7.2d, v0.2d
    fadd    v7.2d, v7.2d, v1.2d

    fmul    v8.2d, v8.2d, v0.2d
    fadd    v8.2d, v8.2d, v1.2d

    fmul    v9.2d, v9.2d, v0.2d
    fadd    v9.2d, v9.2d, v1.2d

    fmul    v10.2d, v10.2d, v0.2d
    fadd    v10.2d, v10.2d, v1.2d

    fmul    v11.2d, v11.2d, v0.2d
    fadd    v11.2d, v11.2d, v1.2d

    fmul    v12.2d, v12.2d, v0.2d
    fadd    v12.2d, v12.2d, v1.2d

    fmul    v13.2d, v13.2d, v0.2d
    fadd    v13.2d, v13.2d, v1.2d

    fmul    v14.2d, v14.2d, v0.2d
    fadd    v14.2d, v14.2d, v1.2d

    subs    x0, x0, #1
    bne     FMA_ARM_f64_NEON_loop

    ret


#ifdef HAVE_SVE
.global FMA_ARM_f64_SVE

FMA_ARM_f64_SVE:
    dup z0.d, d0   
    dup z1.d, d1  
    dup z2.d, d2    

    ptrue   p0.d

    mov     z3.d,  z2.d
    mov     z4.d,  z2.d
    mov     z5.d,  z2.d
    mov     z6.d,  z2.d
    mov     z7.d,  z2.d
    mov     z8.d,  z2.d
    mov     z9.d,  z2.d
    mov     z10.d, z2.d
    mov     z11.d, z2.d
    mov     z12.d, z2.d
    mov     z13.d, z2.d
    mov     z14.d, z2.d

FMA_ARM_f64_SVE_loop:
    fmla    z3.d,  p0/m, z0.d, z1.d
    fmla    z4.d,  p0/m, z0.d, z1.d
    fmla    z5.d,  p0/m, z0.d, z1.d
    fmla    z6.d,  p0/m, z0.d, z1.d
    fmla    z7.d,  p0/m, z0.d, z1.d
    fmla    z8.d,  p0/m, z0.d, z1.d
    fmla    z9.d,  p0/m, z0.d, z1.d
    fmla    z10.d, p0/m, z0.d, z1.d
    fmla    z11.d, p0/m, z0.d, z1.d
    fmla    z12.d, p0/m, z0.d, z1.d
    fmla    z13.d, p0/m, z0.d, z1.d
    fmla    z14.d, p0/m, z0.d, z1.d

    subs    x0, x0, #1
    bne     FMA_ARM_f64_SVE_loop

    ret
#endif