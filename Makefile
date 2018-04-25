all:
	as -mfpu=neon src/arm_neon_complex.s -o arm_neon_complex.o
	gcc arm_neon_complex.o examples/multiply.c -Iinclude/ -o multiply
