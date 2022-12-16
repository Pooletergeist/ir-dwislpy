	.data
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
	sw $ra,-4($sp)
	sw $fp,-8($sp)
	move $fp, $sp
	addi $sp,$sp,-24
main_done:
	lw $ra,-4($fp)
	lw $fp,-8($fp)
	addi $sp,$sp,24
	jr $ra
good:
	sw $ra,-16($sp)
	sw $fp,-20($sp)
	move $fp, $sp
	addi $sp,$sp,-40
	sw $a0,0($fp)
L_5:
	j L_6
L_6:
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
	j L_5
L_7:
	li $t0,0
	sw $t0,-12($fp)
	lw $v0,-12($fp)
	j good_done
good_done:
	lw $ra,-16($fp)
	lw $fp,-20($fp)
	addi $sp,$sp,40
	jr $ra
