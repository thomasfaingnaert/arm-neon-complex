.text
.thumb_func
.balign 4
.syntax unified
.global arm_neon_complex_multiply
.global arm_neon_complex_multiply_accumulate

@ NOTE: COUNT SHOULD BE A MULTIPLE OF 8!

@
@ void arm_neon_complex_multiply(float* result, float* x, float* y, unsigned int count);
@
@ Inspired by: http://a-hackers-craic.blogspot.be/2012/10/neon-complex-multiply.html

arm_neon_complex_multiply:
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    @ Arguments:
    @ r0: result
    @ r1: x
    @ r2: y
    @ r3: count
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

.loop_mul_begin:
    vld2.32     { d16-d19 }, [r1]!  @ q8 = x[0..3].r, q9 = x[0..3].i
    vld2.32     { d24-d27 }, [r2]!  @ q12 = y[0..3].r, q13 = y[0..3].i
    vld2.32     { d20-d23 }, [r1]!  @ q10 = x[4..7].r, q11 = x[4..7].i
    vld2.32     { d28-d31 }, [r2]!  @ q14 = y[4..7].r, q15 = y[4..7].i

    vmul.f32    q0, q8, q12         @ q0 = x[0..3].r * y[0..3].r
    vmul.f32    q1, q9, q12         @ q1 = x[0..3].i * y[0..3].r
    vmul.f32    q2, q10, q14        @ q2 = x[4..7].r * y[4..7].r
    vmul.f32    q3, q11, q14        @ q3 = x[4..7].i * y[4..7].r

    vmls.f32    q0, q9, q13         @ q0 = q0 - x[0..3].i * y[0..3].i
    vmla.f32    q1, q8, q13         @ q1 = q1 + x[0..3].r * y[0..3].i
    vmls.f32    q2, q11, q15        @ q2 = q2 - x[4..7].i * y[4..7].i
    vmla.f32    q3, q10, q15        @ q3 = q3 + x[4..7].r * y[4..7].i

    @ Thus:
    @ q0 = res[0..3].r
    @ q1 = res[0..3].i
    @ q2 = res[4..7].r
    @ q3 = res[4..7].i

    @ Store result
    vst2.32     { d0-d3 }, [r0]!
    vst2.32     { d4-d7 }, [r0]!

    @ Decrement count (8 complex multiplications per iteration)
    subs        r3, r3, #8

    @ If result != 0, still elements to process
    bne         .loop_mul_begin

    bx          lr                  @ Return from function

arm_neon_complex_multiply_accumulate:
    bx      lr
