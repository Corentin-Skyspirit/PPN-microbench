.global ADD_ARM_i32
.global ADD_ARM_i64
.global ADD_ARM_f32
.global ADD_ARM_f64

.global ADD_ARM_i64_NEON
.global ADD_ARM_f64_NEON

.section .text

ADD_ARM_i32:
loop1:
    add w0, w0, w0
    add w1, w1, w1
    add w2, w2, w2
    add w3, w3, w3
    add w4, w4, w4
    add w5, w5, w5
    add w6, w6, w6
    add w7, w7, w7
    add w0, w0, w0
    add w1, w1, w1
    add w2, w2, w2
    add w3, w3, w3
    add w4, w4, w4
    add w5, w5, w5
    add w6, w6, w6
    add w7, w7, w7
    
    subs x0, x0, #1
    bgt loop1
    ret

ADD_ARM_i64:
loop2:
    add x0, x0, x0
    add x1, x1, x1
    add x2, x2, x2
    add x3, x3, x3
    add x4, x4, x4
    add x5, x5, x5
    add x6, x6, x6
    add x7, x7, x7
    add x0, x0, x0
    add x1, x1, x1
    add x2, x2, x2
    add x3, x3, x3
    add x4, x4, x4
    add x5, x5, x5
    add x6, x6, x6
    add x7, x7, x7
    
    subs x0, x0, #1
    bgt loop2
    ret

ADD_ARM_f32:
loop3:
    fadd s0, s0, s0
    fadd s1, s1, s1
    fadd s2, s2, s2
    fadd s3, s3, s3
    fadd s4, s4, s4
    fadd s5, s5, s5
    fadd s6, s6, s6
    fadd s7, s7, s7
    fadd s0, s0, s0
    fadd s1, s1, s1
    fadd s2, s2, s2
    fadd s3, s3, s3
    fadd s4, s4, s4
    fadd s5, s5, s5
    fadd s6, s6, s6
    fadd s7, s7, s7

    subs x0, x0, #1
    bgt loop3
    ret

ADD_ARM_f64:
loop4:
    fadd d0, d0, d0
    fadd d1, d1, d1
    fadd d2, d2, d2
    fadd d3, d3, d3
    fadd d4, d4, d4
    fadd d5, d5, d5
    fadd d6, d6, d6
    fadd d7, d7, d7
    fadd d0, d0, d0
    fadd d1, d1, d1
    fadd d2, d2, d2
    fadd d3, d3, d3
    fadd d4, d4, d4
    fadd d5, d5, d5
    fadd d6, d6, d6
    fadd d7, d7, d7

    subs x0, x0, #1
    bgt loop4
    ret

ADD_ARM_i64_NEON:
loop5:
    addp v0.8b, v0.8b, v0.8b
    addp v1.8b, v1.8b, v1.8b
    addp v2.8b, v2.8b, v2.8b
    addp v3.8b, v3.8b, v3.8b
    addp v4.8b, v4.8b, v4.8b
    addp v5.8b, v5.8b, v5.8b
    addp v6.8b, v6.8b, v6.8b
    addp v7.8b, v7.8b, v7.8b
    addp v0.8b, v0.8b, v0.8b
    addp v1.8b, v1.8b, v1.8b
    addp v2.8b, v2.8b, v2.8b
    addp v3.8b, v3.8b, v3.8b
    addp v4.8b, v4.8b, v4.8b
    addp v5.8b, v5.8b, v5.8b
    addp v6.8b, v6.8b, v6.8b
    addp v7.8b, v7.8b, v7.8b

    subs x0, x0, #1
    bgt loop5
    ret
    
ADD_ARM_f64_NEON:
loop6:
    faddp v0.2d, v0.2d, v0.2d
    faddp v1.2d, v1.2d, v1.2d
    faddp v2.2d, v2.2d, v2.2d
    faddp v3.2d, v3.2d, v3.2d
    faddp v4.2d, v4.2d, v4.2d
    faddp v5.2d, v5.2d, v5.2d
    faddp v6.2d, v6.2d, v6.2d
    faddp v7.2d, v7.2d, v7.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v1.2d, v1.2d, v1.2d
    faddp v2.2d, v2.2d, v2.2d
    faddp v3.2d, v3.2d, v3.2d
    faddp v4.2d, v4.2d, v4.2d
    faddp v5.2d, v5.2d, v5.2d
    faddp v6.2d, v6.2d, v6.2d
    faddp v7.2d, v7.2d, v7.2d

    subs x0, x0, #1
    bgt loop6
    ret

