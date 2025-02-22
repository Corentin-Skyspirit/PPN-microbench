.global ADD_ARM_i32
.global ADD_ARM_i64
.global ADD_ARM_f32
.global ADD_ARM_f64

.global ADD_ARM_i64_NEON
.global ADD_ARM_f64_NEON

.section .text

ADD_ARM_i32:
loop1:
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    add w1, w1, w1
    
    subs x0, x0, #1
    bgt loop1
    ret

ADD_ARM_i64:
loop2:
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    add x1, x1, x1
    
    subs x0, x0, #1
    bgt loop2
    ret

ADD_ARM_f32:
loop3:
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0
    fadd s0, s0, s0

    subs x0, x0, #1
    bgt loop3
    ret

ADD_ARM_f64:
loop4:
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0
    fadd d0, d0, d0

    subs x0, x0, #1
    bgt loop4
    ret

ADD_ARM_i64_NEON:
loop5:
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b
    addp v0.8b, v0.8b, v0.8b

    subs x0, x0, #1
    bgt loop5
    ret
    
ADD_ARM_f64_NEON:
loop6:
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d
    faddp v0.2d, v0.2d, v0.2d

    subs x0, x0, #1
    bgt loop6
    ret

