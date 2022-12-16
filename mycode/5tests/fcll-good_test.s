	.data
L_8:
	.asciiz "one"
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
	li $t0,1
	sw $t0,-4($fp)
	lw $a0,-4($fp)
	la $t0,L_8
	sw $t0,-8($fp)
	lw $a0,-8($fp)
	li $t0,1
	sw $t0,-12($fp)
	lw $a0,-12($fp)
	jal good
main_done:
	lw $ra,-16($fp)
	lw $fp,-20($fp)
	addi $sp,$sp,40
	jr $ra
good:
	sw $ra,-16($sp)
	sw $fp,-20($sp)
	move $fp, $sp
	addi $sp,$sp,-40
	sw $a0,0($fp)
	sw $a1,4($fp)
	sw $a2,8($fp)
	lw $t1,8($fp)
	bgtz $t1,L_5
	j L_6
L_5:
	lw $t1,4($fp)
	move $t0,$t1
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
	lw $t1,0($fp)
	move $t0,$t1
	sw $t0,-12($fp)
	lw $v0,-12($fp)
	j good_done
good_done:
	lw $ra,-16($fp)
	lw $fp,-20($fp)
	addi $sp,$sp,40
	jr $ra
