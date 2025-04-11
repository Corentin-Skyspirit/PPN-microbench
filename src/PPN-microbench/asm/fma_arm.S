.global FMA_ARM_f64_NEON

FMA_ARM_f64_NEON:
    dup.2d  v0, d0 
    dup.2d  v1, d1 
    dup.2d  v2, d2    

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
