# Fast Inverse Square Root
	.text
	.globl main
main:	# $f4 = x
	# $f6 = 0.5f, xhalf, temp
	# $t0 = i
	# $t1 = 0x5f3759df
	# $f8 = 1.5f
	
	# Print msg1
	li 	$v0, 4		# print string syscall code 
	la 	$a0, msg1 	
	syscall
	
	# Get x from user 
	li 	$v0, 6		# read float
	syscall			# result in $f0
	movf.s 	$f4, $f0
	
	# Initialize constants
	l.s	$f6, fp1
	l.s 	$f8, fp2
	li	$t1, 0x5f3759df
	
	# Integer arithmetic
	mul.s	$f6, $f4, $f6	# xhalf = x * 0.5f
	mfc1 	$t0, $f4	# move floating point to integer
	srl	$t0, $t0, 1	# i = i >> 1
	sub	$t0, $t1, $t0	# i = 0x5f3759df - i
	mtc1	$t0, $f4	# move integer to floating point
	
	# Newton's method
	mul.s	$f6, $f6, $f4	# xhalf*x
	mul.s	$f6, $f6, $f4	# xhalf*x*x
	sub.s	$f6, $f8, $f6	# 1.5f - xhalf*x*x
	mul.s	$f4, $f4, $f6	# x = x * above result
	
	# Print x
	li	$v0, 2		# print float
	movf.s	$f12, $f4
	syscall
	
	li	$v0, 10		# exit
	syscall
	
	
	.data
msg1: 	.asciiz "Number to inverse square root? "

fp1:	.float 0.5
fp2:	.float 1.5
	
