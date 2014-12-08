# Learning floating point operations

	.text
	.globl main
main:	# $f4 = S (number to square root)
	# $f6 = x (estimation)
	# $f8 = S/x
	# $f10 = 2
	# $f14 = last_x
	
	# Print msg1
	li 	$v0, 4		# print string syscall code 
	la 	$a0, msg1 	
	syscall
	
	# Get S from user 
	li 	$v0, 6		# read float
	syscall			# result in $f0
	movf.s 	$f4, $f0
	
	# Initialize x, 2
	movf.s 	$f6, $f4
	l.s   	$f10, fp1	# load float 2
	div.s 	$f6, $f6, $f10	# divide by 2 for estimate (optional)
	
loop:	movf.s	$f14, $f6	# last x = x
	div.s 	$f8, $f4, $f6	# S/x
	add.s	$f6, $f6, $f8	# x = x + S/x
	div.s 	$f6, $f6, $f10	# x = x/2
	c.eq.s  1, $f6, $f14	# if x == last_x set flag 1 to True
	bc1t 	1, exit		# branch to exit
	j	loop		
	
	# Print S
exit:	li	$v0, 2		# print float 
	movf.s 	$f12, $f6	
	syscall			# prints $f12
	
	li 	$v0, 10		# exit
	syscall
	
		
	.data
msg1:	.asciiz "Number to squareroot? " 

fp1:	.float 2
