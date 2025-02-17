.global ADD_ARM_i32
.global ADD_ARM_i64
.global ADD_ARM_f32
.global ADD_ARM_f64

.section .text

ADD_ARM_i32:
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    add w0, w0, w0
    
    ret

ADD_ARM_i64:
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0
    add x0, x0, x0

    ret

ADD_ARM_f32:
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

    ret

ADD_ARM_f64:
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

    ret
