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

hanoi:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -32
                               #PARAM vv1    0
                               #PARAM vv2    0
                               #PARAM vv3    0
                               #PARAM vv4    0
                               #IF vv1 != #1 GOTO label2    0
  lw $t0, 8($fp)
  li $t1, 1
  bne $t0, $t1 label2
                               #tt5 := vv2 * #1000000    1
  lw $t0, 12($fp)
  li $t1, 1000000
  mul $t2, $t0, $t1
  sw $t2, -8($fp)
                               #tt4 := tt5 + vv4    0
  lw $t0, -8($fp)
  lw $t1, 20($fp)
  add $t2, $t0, $t1
  sw $t2, -12($fp)
                               #WRITE tt4    0
  lw $t0, -12($fp)
  move $a0, $t0
  jal write
                               #GOTO label3    0
  j label3
                               #LABEL label2 :    1
label2:
                               #tt13 := vv1 - #1    0
  lw $t0, 8($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -16($fp)
                               #ARG vv3    1
  lw $t0, 16($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG vv4    0
  lw $t0, 20($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG vv2    0
  lw $t0, 12($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG tt13    0
  lw $t0, -16($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #tt9 := CALL hanoi    1
  addi $sp, $sp, -4
  jal hanoi
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  move $t0, $v0
  sw $t0, -20($fp)
                               #tt18 := vv2 * #1000000    1
  lw $t0, 12($fp)
  li $t1, 1000000
  mul $t2, $t0, $t1
  sw $t2, -24($fp)
                               #tt17 := tt18 + vv4    0
  lw $t0, -24($fp)
  lw $t1, 20($fp)
  add $t2, $t0, $t1
  sw $t2, -28($fp)
                               #WRITE tt17    0
  lw $t0, -28($fp)
  move $a0, $t0
  jal write
                               #tt26 := vv1 - #1    0
  lw $t0, 8($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -32($fp)
                               #ARG vv4    1
  lw $t0, 20($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG vv2    0
  lw $t0, 12($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG vv3    0
  lw $t0, 16($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG tt26    0
  lw $t0, -32($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #tt22 := CALL hanoi    1
  addi $sp, $sp, -4
  jal hanoi
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  move $t0, $v0
  sw $t0, -36($fp)
                               #LABEL label3 :    1
label3:
                               #RETURN #0    0
  li $v0, 0
  lw $ra, -4($fp)
  jr $ra

main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  addi $sp, $sp, -8
                               #vv5 := #3    0
  li $t0, 3
  sw $t0, -8($fp)
                               #ARG #3    1
  li $t0, 3
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG #2    0
  li $t0, 2
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG #1    0
  li $t0, 1
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG vv5    0
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #tt31 := CALL hanoi    1
  addi $sp, $sp, -4
  jal hanoi
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  move $t0, $v0
  sw $t0, -12($fp)
                               #RETURN #0    1
  li $v0, 0
  lw $ra, -4($fp)
  jr $ra
