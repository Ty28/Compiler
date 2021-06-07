.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra
  
write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

func:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $ra, 0($sp)
                               #PARAM a1
                               #PARAM a2
                               #PARAM a3
                               #PARAM a4
                               #PARAM a5
                               #WRITE a1
  lw $t0, 4($fp)
  move $a0, $t0
  jal write
                               #WRITE a2
  lw $t0, 8($fp)
  move $a0, $t0
  jal write
                               #RETURN a3
  lw $t0, 12($fp)
  move $v0, $t0
  lw $ra, -4($fp)
  jr $ra

main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $ra, 0($sp)
                               #c := #0
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -8($fp)
                               #DEC ac 4028
  addi $sp, $sp, -4028
label1:
  addi $sp, $fp, -4036
                               #IF c >= #99 GOTO label3
  lw $t0, -8($fp)
  li $t1, 99
  bge $t0, $t1 label3
                               #tt13 := #4 * c
  lw $t1, -8($fp)
  addi $sp, $sp, -4
  li $t0, 4
  mul $t2, $t0, $t1
  sw $t2, -4040($fp)
                               #tt9 := &ac + tt13
  addi $t0, $fp, -4036
  lw $t1, -4040($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -4044($fp)
                               #tt14 := c * c
  lw $t0, -8($fp)
  lw $t1, -8($fp)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -4048($fp)
                               #*tt9 := tt14
  lw $t0, -4044($fp)
  lw $t1, -4048($fp)
  sw $t1, 0($t0)
                               #tt18 := c + #1
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  addi $t2, $t0, 1
  sw $t2, -4052($fp)
                               #c := tt18
  lw $t1, -4052($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #GOTO label1
  j label1
label3:
  addi $sp, $fp, -4052
                               #READ tt22
  jal read
  addi $sp, $sp, -4
  move $t0, $v0
  sw $t0, -4056($fp)
                               #b := tt22
  addi $sp, $sp, -4
  lw $t1, -4056($fp)
  move $t0, $t1
  sw $t0, -4060($fp)
                               #ARG #5
  li $t0, 5
  addi $sp, $sp, -4
  sw $t0, -4064($fp)
                               #ARG #4
  li $t0, 4
  addi $sp, $sp, -4
  sw $t0, -4068($fp)
                               #ARG #3
  li $t0, 3
  addi $sp, $sp, -4
  sw $t0, -4072($fp)
                               #ARG #2
  li $t0, 2
  addi $sp, $sp, -4
  sw $t0, -4076($fp)
                               #ARG #1
  li $t0, 1
  addi $sp, $sp, -4
  sw $t0, -4080($fp)
                               #tt23 := CALL func
  jal func
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  addi $sp, $sp, -4
  move $t0, $v0
  sw $t0, -4084($fp)
                               #IF b >= #0 GOTO label5
  lw $t0, -4060($fp)
  li $t1, 0
  bge $t0, $t1 label5
                               #tt32 := b * b
  lw $t0, -4060($fp)
  lw $t1, -4060($fp)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -4088($fp)
                               #WRITE tt32
  lw $t0, -4088($fp)
  move $a0, $t0
  jal write
                               #GOTO label6
  j label6
label5:
  addi $sp, $fp, -4088
                               #WRITE b
  lw $t0, -4060($fp)
  move $a0, $t0
  jal write
label6:
  addi $sp, $fp, -4088
                               #RETURN #0
  li $v0, 0
  lw $ra, -4($fp)
  jr $ra
