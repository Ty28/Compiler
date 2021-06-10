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

process:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $ra, 0($sp)
                               #PARAM vv1
                               #vv2 := #34
  addi $sp, $sp, -4
  li $t0, 34
  sw $t0, -8($fp)
                               #tt7 := vv1 * vv2
  lw $t0, 4($fp)
  lw $t1, -8($fp)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -12($fp)
                               #tt6 := tt7 - vv1
  lw $t0, -12($fp)
  lw $t1, 4($fp)
  addi $sp, $sp, -4
  sub $t2, $t0, $t1
  sw $t2, -16($fp)
                               #tt11 := vv2 * vv1
  lw $t0, -8($fp)
  lw $t1, 4($fp)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -20($fp)
                               #tt5 := tt6 + tt11
  lw $t0, -16($fp)
  lw $t1, -20($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -24($fp)
                               #tt14 := vv2 * vv2
  lw $t0, -8($fp)
  lw $t1, -8($fp)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -28($fp)
                               #tt4 := tt5 + tt14
  lw $t0, -24($fp)
  lw $t1, -28($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -32($fp)
                               #tt3 := tt4 + #18
  lw $t0, -32($fp)
  addi $sp, $sp, -4
  li $t1, 18
  add $t2, $t0, $t1
  sw $t2, -36($fp)
                               #vv2 := tt3
  lw $t1, -36($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #tt21 := vv2 * #3
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  li $t1, 3
  mul $t2, $t0, $t1
  sw $t2, -40($fp)
                               #tt24 := vv1 * #3
  lw $t0, 4($fp)
  addi $sp, $sp, -4
  li $t1, 3
  mul $t2, $t0, $t1
  sw $t2, -44($fp)
                               #tt20 := tt21 - tt24
  lw $t0, -40($fp)
  lw $t1, -44($fp)
  addi $sp, $sp, -4
  sub $t2, $t0, $t1
  sw $t2, -48($fp)
                               #tt19 := tt20 + #335
  lw $t0, -48($fp)
  addi $sp, $sp, -4
  li $t1, 335
  add $t2, $t0, $t1
  sw $t2, -52($fp)
                               #vv2 := tt19
  lw $t1, -52($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #RETURN vv2
  lw $t0, -8($fp)
  move $v0, $t0
  lw $ra, -4($fp)
  jr $ra

mod:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $ra, 0($sp)
                               #PARAM vv3
                               #PARAM vv4
                               #tt32 := vv3 / vv4
  lw $t0, 4($fp)
  lw $t1, 8($fp)
  addi $sp, $sp, -4
  div $t0, $t1
  mflo $t2
  sw $t2, -8($fp)
                               #tt31 := tt32 * vv4
  lw $t0, -8($fp)
  lw $t1, 8($fp)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -12($fp)
                               #tt29 := vv3 - tt31
  lw $t0, 4($fp)
  lw $t1, -12($fp)
  addi $sp, $sp, -4
  sub $t2, $t0, $t1
  sw $t2, -16($fp)
                               #RETURN tt29
  lw $t0, -16($fp)
  move $v0, $t0
  lw $ra, -4($fp)
  jr $ra

main:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $ra, 0($sp)
                               #vv5 := #5
  addi $sp, $sp, -4
  li $t0, 5
  sw $t0, -8($fp)
                               #vv6 := #7
  addi $sp, $sp, -4
  li $t0, 7
  sw $t0, -12($fp)
                               #vv7 := #11
  addi $sp, $sp, -4
  li $t0, 11
  sw $t0, -16($fp)
                               #tt58 := vv5 + vv6
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -20($fp)
                               #vv8 := tt58
  addi $sp, $sp, -4
  lw $t1, -20($fp)
  move $t0, $t1
  sw $t0, -24($fp)
                               #tt62 := vv5 + vv6
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -28($fp)
                               #tt65 := vv7 / #1
  lw $t0, -16($fp)
  addi $sp, $sp, -4
  li $t1, 1
  div $t0, $t1
  mflo $t2
  sw $t2, -32($fp)
                               #tt61 := tt62 + tt65
  lw $t0, -28($fp)
  lw $t1, -32($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -36($fp)
                               #vv9 := tt61
  addi $sp, $sp, -4
  lw $t1, -36($fp)
  move $t0, $t1
  sw $t0, -40($fp)
                               #tt69 := vv5 * vv6
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -44($fp)
                               #tt68 := tt69 - vv7
  lw $t0, -44($fp)
  lw $t1, -16($fp)
  addi $sp, $sp, -4
  sub $t2, $t0, $t1
  sw $t2, -48($fp)
                               #vv10 := tt68
  addi $sp, $sp, -4
  lw $t1, -48($fp)
  move $t0, $t1
  sw $t0, -52($fp)
                               #vv11 := #42
  addi $sp, $sp, -4
  li $t0, 42
  sw $t0, -56($fp)
                               #vv12 := #4
  addi $sp, $sp, -4
  li $t0, 4
  sw $t0, -60($fp)
                               #vv13 := #0
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -64($fp)
                               #vv14 := #0
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -68($fp)
                               #DEC vv15 16
  addi $sp, $sp, -16
                               #tt81 := vv5 + vv6
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -88($fp)
                               #tt80 := tt81 + vv7
  lw $t0, -88($fp)
  lw $t1, -16($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -92($fp)
                               #tt79 := tt80 + #1500
  lw $t0, -92($fp)
  addi $sp, $sp, -4
  li $t1, 1500
  add $t2, $t0, $t1
  sw $t2, -96($fp)
                               #tt78 := tt79 - vv10
  lw $t0, -96($fp)
  lw $t1, -52($fp)
  addi $sp, $sp, -4
  sub $t2, $t0, $t1
  sw $t2, -100($fp)
                               #vv10 := tt78
  lw $t1, -100($fp)
  move $t0, $t1
  sw $t0, -52($fp)
label1:
  addi $sp, $fp, -100
                               #IF vv13 >= #4 GOTO label3
  lw $t0, -64($fp)
  li $t1, 4
  bge $t0, $t1 label3
                               #tt90 := #15 * vv13
  lw $t1, -64($fp)
  addi $sp, $sp, -4
  li $t0, 15
  mul $t2, $t0, $t1
  sw $t2, -104($fp)
                               #vv14 := tt90
  lw $t1, -104($fp)
  move $t0, $t1
  sw $t0, -68($fp)
                               #tt97 := #4 * vv13
  lw $t1, -64($fp)
  addi $sp, $sp, -4
  li $t0, 4
  mul $t2, $t0, $t1
  sw $t2, -108($fp)
                               #tt93 := &vv15 + tt97
  addi $t0, $fp, -84
  lw $t1, -108($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -112($fp)
                               #*tt93 := vv14
  lw $t0, -112($fp)
  lw $t1, -68($fp)
  sw $t1, 0($t0)
                               #tt100 := vv13 + #1
  lw $t0, -64($fp)
  addi $sp, $sp, -4
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -116($fp)
                               #vv13 := tt100
  lw $t1, -116($fp)
  move $t0, $t1
  sw $t0, -64($fp)
                               #GOTO label1
  j label1
label3:
  addi $sp, $fp, -116
                               #IF vv13 >= #7 GOTO label6
  lw $t0, -64($fp)
  li $t1, 7
  bge $t0, $t1 label6
                               #ARG #2
  li $t0, 2
  addi $sp, $sp, -4
  sw $t0, -120($fp)
                               #ARG vv10
  lw $t0, -52($fp)
  addi $sp, $sp, -4
  sw $t0, -124($fp)
  lw $t5, -136($fp)
  move $t7, $fp
                               #tt105 := CALL mod
  jal mod
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  lw $t5, -136($fp)
  move $t7, $fp
  addi $sp, $sp, -4
  move $t0, $v0
  sw $t0, -128($fp)
                               #IF tt105 <= #0 GOTO label8
  lw $t0, -128($fp)
  li $t1, 0
  ble $t0, $t1 label8
                               #tt110 := vv13 - #1
  lw $t0, -64($fp)
  addi $sp, $sp, -4
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -132($fp)
                               #vv16 := tt110
  addi $sp, $sp, -4
  lw $t1, -132($fp)
  move $t0, $t1
  sw $t0, -136($fp)
label8:
  addi $sp, $fp, -136
                               #ARG vv5
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  sw $t0, -140($fp)
                               #tt113 := CALL process
  jal process
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  addi $sp, $sp, -4
  move $t0, $v0
  sw $t0, -144($fp)
                               #tt118 := vv5 + #3
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  li $t1, 3
  add $t2, $t0, $t1
  sw $t2, -148($fp)
                               #tt117 := tt118 - #2
  lw $t0, -148($fp)
  addi $sp, $sp, -4
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -152($fp)
                               #tt116 := tt117 - #1
  lw $t0, -152($fp)
  addi $sp, $sp, -4
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -156($fp)
                               #ARG tt116
  lw $t0, -156($fp)
  addi $sp, $sp, -4
  sw $t0, -160($fp)
                               #tt114 := CALL process
  jal process
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  addi $sp, $sp, -4
  move $t0, $v0
  sw $t0, -164($fp)
                               #IF tt113 != tt114 GOTO label10
  lw $t0, -144($fp)
  lw $t1, -164($fp)
  bne $t0, $t1 label10
                               #tt125 := vv10 - #2
  lw $t0, -52($fp)
  addi $sp, $sp, -4
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -168($fp)
                               #tt124 := tt125 + #1
  lw $t0, -168($fp)
  addi $sp, $sp, -4
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -172($fp)
                               #vv10 := tt124
  lw $t1, -172($fp)
  move $t0, $t1
  sw $t0, -52($fp)
label10:
  addi $sp, $fp, -172
                               #tt131 := vv5 + #2
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  li $t1, 2
  add $t2, $t0, $t1
  sw $t2, -176($fp)
                               #tt130 := tt131 + #1
  lw $t0, -176($fp)
  addi $sp, $sp, -4
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -180($fp)
                               #vv5 := tt130
  lw $t1, -180($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #tt136 := vv13 + #1
  lw $t0, -64($fp)
  addi $sp, $sp, -4
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -184($fp)
                               #vv13 := tt136
  lw $t1, -184($fp)
  move $t0, $t1
  sw $t0, -64($fp)
                               #tt140 := vv13 + #1
  lw $t0, -64($fp)
  addi $sp, $sp, -4
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -188($fp)
                               #vv13 := tt140
  lw $t1, -188($fp)
  move $t0, $t1
  sw $t0, -64($fp)
                               #GOTO label3
  j label3
label6:
  addi $sp, $fp, -188
                               #tt148 := #4 * #0
  addi $sp, $sp, -4
  li $t0, 4
  li $t1, 0
  mul $t2, $t0, $t1
  sw $t2, -192($fp)
                               #tt144 := &vv15 + tt148
  addi $t0, $fp, -84
  lw $t1, -192($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -196($fp)
                               #WRITE *tt144
  lw $t0, -196($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #tt154 := #4 * #1
  addi $sp, $sp, -4
  li $t0, 4
  li $t1, 1
  mul $t2, $t0, $t1
  sw $t2, -200($fp)
                               #tt150 := &vv15 + tt154
  addi $t0, $fp, -84
  lw $t1, -200($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -204($fp)
                               #WRITE *tt150
  lw $t0, -204($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #tt160 := #4 * #2
  addi $sp, $sp, -4
  li $t0, 4
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -208($fp)
                               #tt156 := &vv15 + tt160
  addi $t0, $fp, -84
  lw $t1, -208($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -212($fp)
                               #WRITE *tt156
  lw $t0, -212($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #tt166 := #4 * #3
  addi $sp, $sp, -4
  li $t0, 4
  li $t1, 3
  mul $t2, $t0, $t1
  sw $t2, -216($fp)
                               #tt162 := &vv15 + tt166
  addi $t0, $fp, -84
  lw $t1, -216($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -220($fp)
                               #WRITE *tt162
  lw $t0, -220($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #RETURN #0
  li $v0, 0
  lw $ra, -4($fp)
  jr $ra
