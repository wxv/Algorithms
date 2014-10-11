# Optimized Bubble Sort in MIPS
# https://en.wikipedia.org/wiki/Bubble_sort#Optimizing_bubble_sort
	.text
	.globl main
main:	la	$s0, list	# Load list address
	li	$s1, 10		# Length of list
	
loop:	li	$t0, 0		# swapped = false
	li 	$t1, 1		# for loop "i"
	
for:	beq	$t1, $s1, fend	# break if i==length
	
	move	$t2, $t1	# Temporary index
	add	$t2, $t2, $t2	# Multiply by 2 twice
	add	$t2, $t2, $t2	
	add	$t2, $t2, $s0	# Combined address
	lw	$t3, 0($t2)	# list[i]
	lw	$t4, -4($t2)	# list[i-1]
	
	addi	$t1, $t1, 1	# i++
	
	ble 	$t4, $t3, for	# if list[i-1] > list[i]
	sw	$t3, -4($t2)	# list[i-1] = temp list[i]
	sw	$t4, 0($t2)	# list[i] = temp list[i-1]
	li	$t0, 1		# swapped = true
	j	for

fend:	subi 	$s1, $s1, 1	# length--
	bnez 	$t0, loop	# Repeat if swapped==true
	
	li	$v0, 10		
	syscall

	
	.data
list:	.word 12, 5, 0, -2, 1, 7, 3, 9, 25, 9