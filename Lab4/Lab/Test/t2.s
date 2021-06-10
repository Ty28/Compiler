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
                               #RETURN #0
  li $v0, 0
  lw $ra, -4($fp)
  jr $ra

main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $ra, 0($sp)
                               #c := #0
  lw $t7, -4($fp)
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -8($fp)
                               #DEC ac 4028
  lw $t7, -4($fp)                             
  addi $sp, $sp, -4028
label1:
  addi $sp, $fp, -4036
                               #IF c >= #2 GOTO label3
  lw $t7, -4($fp)
  lw $t0, -8($fp)
  li $t1, 2
  bge $t0, $t1 label3
                               #tt13 := #4 * c
  lw $t7, -4($fp)
  lw $t1, -8($fp)
  addi $sp, $sp, -4
  li $t0, 4
  mul $t2, $t0, $t1
  sw $t2, -4040($fp)
                               #tt9 := &ac + tt13
  lw $t7, -4($fp)
  addi $t0, $fp, -8
  lw $t1, -4040($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -4044($fp)
                               #*tt9 := c
  lw $t7, -4($fp)
  lw $t0, -4044($fp)
  lw $t1, -8($fp)
  sw $t1, 0($t0)
                               #tt16 := c + #1
  lw $t7, -4($fp)
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  addi $t2, $t0, 1
  sw $t2, -4048($fp)
                               #c := tt16
  lw $t7, -4($fp)
  lw $t1, -4048($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #GOTO label1
  lw $t7, -4($fp)
  j label1
label3:
  lw $t7, -4($fp)
  addi $sp, $fp, -4048
                               #RETURN #0
  li $v0, 0
  lw $ra, -4($fp)
  jr $ra