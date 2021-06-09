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
                               #IF vv13 >= #7 GOTO label6
  lw $t0, -64($fp)
  li $t1, 7
  bge $t0, $t1 label6
                               #WRITE vv10
  lw $t0, -52($fp)
  move $a0, $t0
  jal write
                               #ARG #2
  li $t0, 2
  addi $sp, $sp, -4
  sw $t0, -120($fp)
                               #ARG vv10
  lw $t0, -52($fp)
  addi $sp, $sp, -4
  sw $t0, -124($fp)
                               #tt107 := CALL mod
  jal mod
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  addi $sp, $sp, -4
  move $t0, $v0
  sw $t0, -128($fp)
                               #IF tt107 <= #0 GOTO label8
  lw $t0, -128($fp)
  li $t1, 0
  ble $t0, $t1 label8
                               #tt112 := vv13 - #1
  lw $t0, -64($fp)
  addi $sp, $sp, -4
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -132($fp)
                               #vv16 := tt112
  addi $sp, $sp, -4
  lw $t1, -132($fp)
  move $t0, $t1
  sw $t0, -136($fp)
label8:
                               #ARG vv5
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  sw $t0, -140($fp)
                               #tt115 := CALL process
  jal process
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  addi $sp, $sp, -4
  move $t0, $v0
  sw $t0, -144($fp)
                               #tt120 := vv5 + #3
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  li $t1, 3
  add $t2, $t0, $t1
  sw $t2, -148($fp)
                               #tt119 := tt120 - #2
  lw $t0, -148($fp)
  addi $sp, $sp, -4
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -152($fp)
                               #tt118 := tt119 - #1
  lw $t0, -152($fp)
  addi $sp, $sp, -4
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -156($fp)
                               #ARG tt118
  lw $t0, -156($fp)
  addi $sp, $sp, -4
  sw $t0, -160($fp)
                               #tt116 := CALL process
  jal process
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  addi $sp, $sp, -4
  move $t0, $v0
  sw $t0, -164($fp)
                               #IF tt115 != tt116 GOTO label10
  lw $t0, -144($fp)
  lw $t1, -164($fp)
  bne $t0, $t1 label10
                               #tt127 := vv10 - #2
  lw $t0, -52($fp)
  addi $sp, $sp, -4
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -168($fp)
                               #tt126 := tt127 + #1
  lw $t0, -168($fp)
  addi $sp, $sp, -4
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -172($fp)
                               #vv10 := tt126
  lw $t1, -172($fp)
  move $t0, $t1
  sw $t0, -52($fp)
label10:
                               #tt133 := vv5 + #2
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  li $t1, 2
  add $t2, $t0, $t1
  sw $t2, -176($fp)
                               #tt132 := tt133 + #1
  lw $t0, -176($fp)
  addi $sp, $sp, -4
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -180($fp)
                               #vv5 := tt132
  lw $t1, -180($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #tt138 := vv13 + #1
  lw $t0, -64($fp)
  addi $sp, $sp, -4
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -184($fp)
                               #vv13 := tt138
  lw $t1, -184($fp)
  move $t0, $t1
  sw $t0, -64($fp)
                               #tt142 := vv13 + #1
  lw $t0, -64($fp)
  addi $sp, $sp, -4
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -188($fp)
                               #vv13 := tt142
  lw $t1, -188($fp)
  move $t0, $t1
  sw $t0, -64($fp)
                               #GOTO label3
  j label3
label6:
                               #tt150 := #4 * #0
  addi $sp, $sp, -4
  li $t0, 4
  li $t1, 0
  mul $t2, $t0, $t1
  sw $t2, -192($fp)
                               #tt146 := &vv15 + tt150
  addi $t0, $fp, -84
  lw $t1, -192($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -196($fp)
                               #WRITE *tt146
  lw $t0, -196($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #tt156 := #4 * #1
  addi $sp, $sp, -4
  li $t0, 4
  li $t1, 1
  mul $t2, $t0, $t1
  sw $t2, -200($fp)
                               #tt152 := &vv15 + tt156
  addi $t0, $fp, -84
  lw $t1, -200($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -204($fp)
                               #WRITE *tt152
  lw $t0, -204($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #tt162 := #4 * #2
  addi $sp, $sp, -4
  li $t0, 4
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -208($fp)
                               #tt158 := &vv15 + tt162
  addi $t0, $fp, -84
  lw $t1, -208($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -212($fp)
                               #WRITE *tt158
  lw $t0, -212($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #tt168 := #4 * #3
  addi $sp, $sp, -4
  li $t0, 4
  li $t1, 3
  mul $t2, $t0, $t1
  sw $t2, -216($fp)
                               #tt164 := &vv15 + tt168
  addi $t0, $fp, -84
  lw $t1, -216($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -220($fp)
                               #WRITE *tt164
  lw $t0, -220($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #RETURN #0
  li $v0, 0
  lw $ra, -4($fp)
  jr $ra
