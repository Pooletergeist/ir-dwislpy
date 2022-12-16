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
	sw $ra,-8($sp)
	sw $fp,-12($sp)
	move $fp, $sp
	addi $sp,$sp,-32
	li $t0,5
	sw $t0,-4($fp)
	lw $a0,-4($fp)
	jal ifif
main_done:
	lw $ra,-8($fp)
	lw $fp,-12($fp)
	addi $sp,$sp,32
	jr $ra
ifif:
	sw $ra,-12($sp)
	sw $fp,-16($sp)
	move $fp, $sp
	addi $sp,$sp,-32
	sw $a0,0($fp)
	j L_5
L_5:
	li $t0,3
	sw $t0,-4($fp)
	lw $v0,-4($fp)
	j ifif_done
	j L_7
L_6:
	li $t0,4
	sw $t0,-8($fp)
	lw $v0,-8($fp)
	j ifif_done
L_7:
ifif_done:
	lw $ra,-12($fp)
	lw $fp,-16($fp)
	addi $sp,$sp,32
	jr $ra
