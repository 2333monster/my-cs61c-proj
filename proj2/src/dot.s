.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
	ebreak
	# Prologue
	li t5,1
	blt a2,t5,exit_36
	blt a3,t5,exit_37
	blt a4,t5,exit_37
	li t0,0 		#result
	li t1,0 		#i
	slli a3,a3,2		
	slli a4,a4,2
loop_start:
	beq t1,a2,loop_end
	lw t2,0(a0)
	lw t3,0(a1)

	mul t4,t2,t3
	add t0,t0,t4

	add a0,a0,a3
	add a1,a1,a4
	addi t1,t1,1
	j loop_start
exit_36:
	li a0 36
	j exit
exit_37:
	li a0 37
	j exit
loop_end:
	# Epilogue
	mv a0 t0
	ret
