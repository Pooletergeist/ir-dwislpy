	.data
L_12:
	.asciiz "bye"
L_8:
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
	sw $ra,-24($sp)
	sw $fp,-28($sp)
	move $fp, $sp
	addi $sp,$sp,-48
	j L_5
L_5:
	la $t0,L_8
	sw $t0,-4($fp)
	li $v0,4
	lw $a0,-4($fp)
	syscall
	la $t0,L_0
	sw $t0,-8($fp)
	li $v0,4
	lw $a0,-8($fp)
	syscall
	j L_7
L_6:
L_7:
	j L_10
L_9:
	la $t0,L_0
	sw $t0,-12($fp)
	li $v0,4
	lw $a0,-12($fp)
	syscall
	j L_11
L_10:
	la $t0,L_12
	sw $t0,-16($fp)
	li $v0,4
	lw $a0,-16($fp)
	syscall
	la $t0,L_0
	sw $t0,-20($fp)
	li $v0,4
	lw $a0,-20($fp)
	syscall
L_11:
main_done:
	lw $ra,-24($fp)
	lw $fp,-28($fp)
	addi $sp,$sp,48
	jr $ra
