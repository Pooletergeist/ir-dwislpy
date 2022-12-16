	.data
L_12:
	.asciiz "half"
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
	sw $ra,-56($sp)
	sw $fp,-60($sp)
	move $fp, $sp
	addi $sp,$sp,-80
	li $t0,4
	sw $t0,-4($fp)
	li $t0,2
	sw $t0,-8($fp)
L_5:
	li $t0,0
	sw $t0,-12($fp)
	lw $t1,-4($fp)
	move $t0,$t1
	sw $t0,-16($fp)
	lw $t1,-12($fp)
	lw $t2,-16($fp)
	blt $t1,$t2,L_6
	j L_7
L_6:
	lw $t1,-4($fp)
	move $t0,$t1
	sw $t0,-20($fp)
	li $t0,2
	sw $t0,-24($fp)
	lw $t1,-20($fp)
	lw $t2,-24($fp)
	beq $t1,$t2,L_11
	j L_9
L_11:
	j L_8
L_8:
	la $t0,L_12
	sw $t0,-28($fp)
	li $v0,4
	lw $a0,-28($fp)
	syscall
	la $t0,L_0
	sw $t0,-32($fp)
	li $v0,4
	lw $a0,-32($fp)
	syscall
	j L_10
L_9:
	j L_13
L_16:
	j L_14
L_13:
	lw $t1,-4($fp)
	move $t0,$t1
	sw $t0,-40($fp)
	lw $t1,-8($fp)
	move $t0,$t1
	sw $t0,-44($fp)
	lw $t1,-40($fp)
	lw $t2,-44($fp)
	mul $t0,$t1,$t2
	sw $t0,-36($fp)
	lw $a0,-36($fp)
	li $v0,1
	syscall
	la $t0,L_0
	sw $t0,-48($fp)
	li $v0,4
	lw $a0,-48($fp)
	syscall
	j L_15
L_14:
L_15:
L_10:
	li $t0,1
	sw $t0,-52($fp)
	lw $t1,-4($fp)
	lw $t2,-52($fp)
	sub $t0,$t1,$t2
	sw $t0,-4($fp)
	j L_5
L_7:
main_done:
	lw $ra,-56($fp)
	lw $fp,-60($fp)
	addi $sp,$sp,80
	jr $ra
