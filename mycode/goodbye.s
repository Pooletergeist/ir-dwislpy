	.data
L_5:
	.asciiz "hi"
L_4:
	.asciiz "12345678901234567890123456789012345678901234567890123456789012345678901234567890"
L_2:
	.asciiz "False"
L_1:
	.asciiz "True"
L_3:
	.asciiz "None"
L_0:
	.asciiz "\n"
	.text
	.globl main
main:
	sw $ra,-16($sp)
	sw $fp,-20($sp)
	move $fp, $sp
	addi $sp,$sp,-40
	la $t0,L_5
	sw $t0,-4($fp)
	lw $t1,-4($fp)
	move $t0,$t1
	sw $t0,-8($fp)
	lw $a0,-8($fp)
	li $v0,1
	syscall
	la $t0,L_0
	sw $t0,-12($fp)
	li $v0,4
	lw $a0,-12($fp)
	syscall
main_done:
	lw $ra,-16($fp)
	lw $fp,-20($fp)
	addi $sp,$sp,40
	jr $ra
