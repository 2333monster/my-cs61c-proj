.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    ebreak
    # Prologue
    li t5, 1
    blt a1, t5, exit_argmax
    li t0,0         #max_index
    lw t1,0(a0)     #max_value
    add t2,x0,x0    #i
    li t5,4
loop_start:
    beq t2,a1,loop_end
    mul t4,t2,t5    #4i
    add t6,a0,t4    #&a0[i]
    lw t3,0(t6)     #a0[i]
    bge t1,t3,loop_continue
    mv t1,t3
    mv t0,t2
loop_continue:
    addi t2,t2,1
    j loop_start
exit_argmax:
    li a0,36
    j exit
loop_end:
    mv a0,t0
    ret
