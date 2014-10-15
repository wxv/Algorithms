# Binary Exponentiation 
	.text
	.globl main
main:	li	$v0, 4
	la	$a0, msg
	syscall
	
	li	$v0, 5
	syscall
	move	$t0, $v0
	li 	$v0, 5
	syscall
	move	$t1, $v0
	li 	$v0, 5
	syscall
	move	$t2, $v0
	
	li	$t3, 1		# result
	rem	$t0, $t0, $t2
	
while:	beqz	$t1, end	# while (b)
	andi	$t4, $t1, 1
	beqz	$t4, l		# if (b & 1)
	mulo	$t3, $t3, $t0	# ignore overflow 
	rem	$t3, $t3, $t2
l:	mulo	$t0, $t0, $t0
	rem	$t0, $t0, $t2
	srl	$t1, $t1, 1
	j	while
	
end:	move	$a0, $t3
	li	$v0, 1
	syscall
	
	li	$v0, 10
	syscall
	
	.data
msg:	.asciiz "Enter a, b, m (result = a^b mod m)\n"