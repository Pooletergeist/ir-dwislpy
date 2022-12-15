	.data
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
	sw $ra,-40($sp)
	sw $fp,-44($sp)
	move $fp, $sp
	addi $sp,$sp,-64
	li $t0,3
	sw $t0,-4($fp)
	lw $t1,-4($fp)
	move $t0,$t1
	sw $t0,-20($fp)
	lw $a0,-20($fp)
	jal sqr
	move $t0,$v0
	sw $t0,-12($fp)
	lw $t1,-4($fp)
	move $t0,$t1
	sw $t0,-28($fp)
	li $t0,1
	sw $t0,-32($fp)
	lw $t1,-28($fp)
	lw $t2,-32($fp)
	add $t0,$t1,$t2
	sw $t0,-24($fp)
	lw $a0,-24($fp)
	jal sqr
	move $t0,$v0
	sw $t0,-16($fp)
	lw $t1,-12($fp)
	lw $t2,-16($fp)
	add $t0,$t1,$t2
	sw $t0,-8($fp)
	lw $a0,-8($fp)
	li $v0,1
	syscall
	la $t0,L_0
	sw $t0,-36($fp)
	li $v0,4
	lw $a0,-36($fp)
	syscall
main_done:
	lw $ra,-40($fp)
	lw $fp,-44($fp)
	addi $sp,$sp,64
	jr $ra
sqr:
	sw $ra,-16($sp)
	sw $fp,-20($sp)
	move $fp, $sp
	addi $sp,$sp,-40
	sw $a0,0($fp)
	lw $t1,0($fp)
	move $t0,$t1
	sw $t0,-8($fp)
	lw $t1,0($fp)
	move $t0,$t1
	sw $t0,-12($fp)
	lw $t1,-8($fp)
	lw $t2,-12($fp)
	mul $t0,$t1,$t2
	sw $t0,-4($fp)
