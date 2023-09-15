.globl classify

.text
# =====================================
# COMMAND LINE ARGUMENTS
# =====================================
# Args:
#   a0 (int)        argc
#   a1 (char**)     argv
#   a1[1] (char*)   pointer to the filepath string of m0
#   a1[2] (char*)   pointer to the filepath string of m1
#   a1[3] (char*)   pointer to the filepath string of input matrix
#   a1[4] (char*)   pointer to the filepath string of output file
#   a2 (int)        silent mode, if this is 1, you should not print
#                   anything. Otherwise, you should print the
#                   classification and a newline.
# Returns:
#   a0 (int)        Classification
# Exceptions:
#   - If there are an incorrect number of command line args,
#     this function terminates the program with exit code 31
#   - If malloc fails, this function terminates the program with exit code 26
#
# Usage:
#   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>
classify:
	# prologue
	addi sp, sp, -64
	sw s0, 12(sp)	# a1
	sw s1, 16(sp)	# a2
	sw s2, 20(sp)	# m0_pointer
	sw s3, 24(sp)	# m1_pointer
	sw s4, 28(sp)	# input_pointer
	sw s5, 32(sp)	
	sw s6, 36(sp)	# num_rows_input
	sw s7, 40(sp)	# num_cols_input
	sw s8, 44(sp)	# num_rows_m1
	sw s9, 48(sp)	# num_cols_m1
	sw s10, 52(sp)	# num_rows_m0
	sw s11, 56(sp)	# num_cols_m0
	sw ra, 60(sp)

	li t0, 5
	bne a0, t0, argnum_error
	mv s0, a1 # store argument pointer
	mv s1, a2 # store switcher

	# Read pretrained m0
	li a0, 4
	jal ra, malloc
	beqz a0, malloc_error
	mv s10, a0 
	li a0, 4
	jal ra, malloc
	beqz a0, malloc_error
	mv s11, a0 
	# read matrix
	lw a0, 4(s0)
	mv a1, s10
	mv a2, s11
	jal ra, read_matrix
	mv s2, a0

	# Read pretrained m1
	li a0, 4
	jal ra, malloc
	beqz a0, malloc_error
	mv s8, a0 
	li a0, 4
	jal ra, malloc
	beqz a0, malloc_error
	mv s9, a0 
	# read matrix
	lw a0, 8(s0)
	mv a1, s8
	mv a2, s9
	jal ra, read_matrix
	mv s3, a0

	# Read input matrix
	ebreak
	li a0, 4
	jal ra, malloc
	beqz a0, malloc_error
	mv s6, a0 
	li a0, 4
	jal ra, malloc
	beqz a0, malloc_error
	mv s7, a0 
	lw a0, 12(s0)
	mv a1, s6
	mv a2, s7
	jal ra, read_matrix
	mv s4, a0

	# Compute h = matmul(m0, input)
	lw t0, 0(s10)
	lw t1, 0(s7)
	# malloc
	mul t0, t0, t1
	sw t0, 8(sp)	# h_size
	slli a0, t0, 2 	# 4-byte per element
	jal ra, malloc
	beqz a0, malloc_error
	sw a0, 0(sp)	# h_pointer

	# matmul
	mv a0, s2
	lw a1, 0(s10)
	lw a2, 0(s11)
	mv a3, s4
	lw a4, 0(s6)
	lw a5, 0(s7)
	lw a6, 0(sp)
	jal ra, matmul

	# Compute h = relu(h)
	lw a0, 0(sp)
	lw a1, 8(sp)
	jal ra, relu

	# Compute o = matmul(m1, h)
	lw t0, 0(s8)
	lw t1, 0(s7)
	# malloc
	mul t0, t0, t1
	sw t0, 8(sp) 	# o_size
	slli a0, t0, 2 	# 4-byte per element
	jal ra, malloc
	sw a0, 4(sp)	# o_pointer

	# matmul
	mv a0, s3
	lw a1, 0(s8)
	lw a2, 0(s9)
	lw a3, 0(sp)
	lw a4, 0(s10)
	lw a5, 0(s7)
	lw a6, 4(sp)
	jal ra, matmul

	# Write output matrix o
	lw a0, 16(s0)
	lw a1, 4(sp)
	lw a2, 0(s8)
	lw a3, 0(s7)
	jal ra, write_matrix

	# Compute and return argmax(o)
	lw a0, 4(sp)
	lw a1, 8(sp)
	jal ra, argmax
	sw a0, 8(sp)	# argmax(o)

	# If enabled, print argmax(o) and newline
	bnez s1, done
	lw a0, 8(sp)
	jal ra, print_int
	li a0, '\n'
	jal ra, print_char
done:
	# free m0
	mv a0, s2
	jal ra, free
	# free m1
	mv a0, s3
	jal ra, free
	# free input
	mv a0, s4
	jal ra, free

	# free h
	lw a0, 0(sp)
	jal ra, free
	# free o
	lw a0, 4(sp)
	jal ra, free

	# free num&col
	mv a0, s6
	jal ra, free
	mv a0, s7
	jal ra, free
	mv a0, s8
	jal ra, free
	mv a0, s9
	jal ra, free
	mv a0, s10
	jal ra, free
	mv a0, s11
	jal ra, free

	# return
	lw a0, 8(sp)


	# epilogue
	lw s0, 12(sp)	
	lw s1, 16(sp)	
	lw s2, 20(sp)	
	lw s3, 24(sp)	
	lw s4, 28(sp)	
	lw s5, 32(sp)	
	lw s6, 36(sp)	
	lw s7, 40(sp)	
	lw s8, 44(sp)	
	lw s9, 48(sp)	
	lw s10, 52(sp)	
	lw s11, 56(sp)
	lw ra, 60(sp)	
	addi sp, sp, 64

	ret
argnum_error:
	li a0, 31
	j exit
malloc_error:
	li a0, 26
	j exit