.global cpu_frequency_arm_64

cpu_frequency_arm_64:
    mov x0, x0 
    mov x1, #0 
    lsl x0, x0, #4 

1:
    add x1, x1, #1
    add x1, x1, #1
    add x1, x1, #1
    add x1, x1, #1

    add x1, x1, #1
    add x1, x1, #1
    add x1, x1, #1
    add x1, x1, #1

    add x1, x1, #1
    add x1, x1, #1
    add x1, x1, #1
    add x1, x1, #1

    add x1, x1, #1
    add x1, x1, #1
    add x1, x1, #1
    add x1, x1, #1

    cmp x1, x0
    blt 1b 

    ret
