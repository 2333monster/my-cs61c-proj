.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:
	ebreak
	# Error checks
	li t5, 1
	blt a1, t5, exit_38
	blt a2, t5, exit_38
	blt a4, t5, exit_38
	blt a5, t5, exit_38
	bne a2, a4, exit_38

	# Prologue
	addi sp, sp, -16
	sw s0, 0(sp)
	sw s1, 4(sp)
	sw s2, 8(sp)
	sw s3, 12(sp)
	li s0, 0     # i
	li s1, 0     # j

outer_loop_start:
	li s1, 0

inner_loop_start:
	# save context
	addi sp, sp, -32
	sw ra, 0(sp)
	sw a0, 4(sp)
	sw a1, 8(sp)
	sw a2, 12(sp)
	sw a3, 16(sp)
	sw a4, 20(sp)
	sw a5, 24(sp)
	sw a6, 28(sp)

	# set arguments for dot function
	addi t4, x0, 4
	mul t4, t4, s1
	add a1, a3, t4
	li a3, 1
	mv a4, a5

	# call dot function
	jal dot

	# get answer
	mv t1, a0

	# restore context
	lw ra, 0(sp)
	lw a0, 4(sp)
	lw a1, 8(sp)
	lw a2, 12(sp)
	lw a3, 16(sp)
	lw a4, 20(sp)
	lw a5, 24(sp)
	lw a6, 28(sp)
	addi sp, sp, 32

	# store result in the result matrix d
	mul t2, s0, a5
	add t2, t2, s1
	addi t4, x0, 4
	mul t2, t2, t4
	add t2, a6, t2
	sw t1, 0(t2)

inner_loop_end:
	addi s1, s1, 1
	beq s1, a5, outer_loop_end
	j inner_loop_start

outer_loop_end:
	addi s0, s0, 1
	addi t4, x0, 4
	mul t0, t4, a2
	add a0, a0, t0
	beq s0, a1, end
	j outer_loop_start


end:
	# Epilogue
	lw s0, 0(sp)
	lw s1, 4(sp)
	lw s2, 8(sp)
	lw s3, 12(sp)
	addi sp, sp, 16
	ret

exit_38:
	li a0, 38
	j exit
