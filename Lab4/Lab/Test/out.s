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

dot_product:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $ra, 0($sp)
                               #PARAM vv1
                               #PARAM vv2
                               #tt8 := #4 * #0
  addi $sp, $sp, -4
  li $t2, 0
  sw $t2, -8($fp)
                               #tt4 := vv1 + tt8
  lw $t0, 4($fp)
  lw $t1, -8($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -12($fp)
                               #tt13 := #4 * #0
  addi $sp, $sp, -4
  li $t2, 0
  sw $t2, -16($fp)
                               #tt9 := vv2 + tt13
  lw $t0, 8($fp)
  lw $t1, -16($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -20($fp)
                               #tt3 := *tt4 * *tt9
  lw $t0, -12($fp)
  lw $t0, 0($t0)
  lw $t1, -20($fp)
  lw $t1, 0($t1)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -24($fp)
                               #tt19 := #4 * #1
  addi $sp, $sp, -4
  li $t2, 4
  sw $t2, -28($fp)
                               #tt15 := vv1 + tt19
  lw $t0, 4($fp)
  lw $t1, -28($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -32($fp)
                               #tt24 := #4 * #1
  addi $sp, $sp, -4
  li $t2, 4
  sw $t2, -36($fp)
                               #tt20 := vv2 + tt24
  lw $t0, 8($fp)
  lw $t1, -36($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -40($fp)
                               #tt14 := *tt15 * *tt20
  lw $t0, -32($fp)
  lw $t0, 0($t0)
  lw $t1, -40($fp)
  lw $t1, 0($t1)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -44($fp)
                               #tt2 := tt3 + tt14
  lw $t0, -24($fp)
  lw $t1, -44($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -48($fp)
                               #tt30 := #4 * #2
  addi $sp, $sp, -4
  li $t2, 8
  sw $t2, -52($fp)
                               #tt26 := vv1 + tt30
  lw $t0, 4($fp)
  lw $t1, -52($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -56($fp)
                               #tt35 := #4 * #2
  addi $sp, $sp, -4
  li $t2, 8
  sw $t2, -60($fp)
                               #tt31 := vv2 + tt35
  lw $t0, 8($fp)
  lw $t1, -60($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -64($fp)
                               #tt25 := *tt26 * *tt31
  lw $t0, -56($fp)
  lw $t0, 0($t0)
  lw $t1, -64($fp)
  lw $t1, 0($t1)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -68($fp)
                               #tt1 := tt2 + tt25
  lw $t0, -48($fp)
  lw $t1, -68($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -72($fp)
                               #RETURN tt1
  lw $t0, -72($fp)
  move $v0, $t0
  lw $ra, -4($fp)
  jr $ra

cross_product:
  addi $sp, $sp, -4
  sw $fp, 0($sp)
  move $fp, $sp
  addi $sp, $sp, -4
  sw $ra, 0($sp)
                               #PARAM vv3
                               #PARAM vv4
                               #PARAM vv5
                               #tt40 := #4 * #0
  addi $sp, $sp, -4
  li $t2, 0
  sw $t2, -8($fp)
                               #tt36 := vv5 + tt40
  lw $t0, 12($fp)
  lw $t1, -8($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -12($fp)
                               #tt47 := #4 * #1
  addi $sp, $sp, -4
  li $t2, 4
  sw $t2, -16($fp)
                               #tt43 := vv3 + tt47
  lw $t0, 4($fp)
  lw $t1, -16($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -20($fp)
                               #tt52 := #4 * #2
  addi $sp, $sp, -4
  li $t2, 8
  sw $t2, -24($fp)
                               #tt48 := vv4 + tt52
  lw $t0, 8($fp)
  lw $t1, -24($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -28($fp)
                               #tt42 := *tt43 * *tt48
  lw $t0, -20($fp)
  lw $t0, 0($t0)
  lw $t1, -28($fp)
  lw $t1, 0($t1)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -32($fp)
                               #tt58 := #4 * #2
  addi $sp, $sp, -4
  li $t2, 8
  sw $t2, -36($fp)
                               #tt54 := vv3 + tt58
  lw $t0, 4($fp)
  lw $t1, -36($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -40($fp)
                               #tt63 := #4 * #1
  addi $sp, $sp, -4
  li $t2, 4
  sw $t2, -44($fp)
                               #tt59 := vv4 + tt63
  lw $t0, 8($fp)
  lw $t1, -44($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -48($fp)
                               #tt53 := *tt54 * *tt59
  lw $t0, -40($fp)
  lw $t0, 0($t0)
  lw $t1, -48($fp)
  lw $t1, 0($t1)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -52($fp)
                               #tt41 := tt42 - tt53
  lw $t0, -32($fp)
  lw $t1, -52($fp)
  addi $sp, $sp, -4
  sub $t2, $t0, $t1
  sw $t2, -56($fp)
                               #*tt36 := tt41
  lw $t0, -12($fp)
  lw $t1, -56($fp)
  sw $t1, 0($t0)
                               #tt68 := #4 * #1
  addi $sp, $sp, -4
  li $t2, 4
  sw $t2, -60($fp)
                               #tt64 := vv5 + tt68
  lw $t0, 12($fp)
  lw $t1, -60($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -64($fp)
                               #tt75 := #4 * #2
  addi $sp, $sp, -4
  li $t2, 8
  sw $t2, -68($fp)
                               #tt71 := vv3 + tt75
  lw $t0, 4($fp)
  lw $t1, -68($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -72($fp)
                               #tt80 := #4 * #0
  addi $sp, $sp, -4
  li $t2, 0
  sw $t2, -76($fp)
                               #tt76 := vv4 + tt80
  lw $t0, 8($fp)
  lw $t1, -76($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -80($fp)
                               #tt70 := *tt71 * *tt76
  lw $t0, -72($fp)
  lw $t0, 0($t0)
  lw $t1, -80($fp)
  lw $t1, 0($t1)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -84($fp)
                               #tt86 := #4 * #0
  addi $sp, $sp, -4
  li $t2, 0
  sw $t2, -88($fp)
                               #tt82 := vv3 + tt86
  lw $t0, 4($fp)
  lw $t1, -88($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -92($fp)
                               #tt91 := #4 * #2
  addi $sp, $sp, -4
  li $t2, 8
  sw $t2, -96($fp)
                               #tt87 := vv4 + tt91
  lw $t0, 8($fp)
  lw $t1, -96($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -100($fp)
                               #tt81 := *tt82 * *tt87
  lw $t0, -92($fp)
  lw $t0, 0($t0)
  lw $t1, -100($fp)
  lw $t1, 0($t1)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -104($fp)
                               #tt69 := tt70 - tt81
  lw $t0, -84($fp)
  lw $t1, -104($fp)
  addi $sp, $sp, -4
  sub $t2, $t0, $t1
  sw $t2, -108($fp)
                               #*tt64 := tt69
  lw $t0, -64($fp)
  lw $t1, -108($fp)
  sw $t1, 0($t0)
                               #tt96 := #4 * #2
  addi $sp, $sp, -4
  li $t2, 8
  sw $t2, -112($fp)
                               #tt92 := vv5 + tt96
  lw $t0, 12($fp)
  lw $t1, -112($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -116($fp)
                               #tt103 := #4 * #0
  addi $sp, $sp, -4
  li $t2, 0
  sw $t2, -120($fp)
                               #tt99 := vv3 + tt103
  lw $t0, 4($fp)
  lw $t1, -120($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -124($fp)
                               #tt108 := #4 * #1
  addi $sp, $sp, -4
  li $t2, 4
  sw $t2, -128($fp)
                               #tt104 := vv4 + tt108
  lw $t0, 8($fp)
  lw $t1, -128($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -132($fp)
                               #tt98 := *tt99 * *tt104
  lw $t0, -124($fp)
  lw $t0, 0($t0)
  lw $t1, -132($fp)
  lw $t1, 0($t1)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -136($fp)
                               #tt114 := #4 * #1
  addi $sp, $sp, -4
  li $t2, 4
  sw $t2, -140($fp)
                               #tt110 := vv3 + tt114
  lw $t0, 4($fp)
  lw $t1, -140($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -144($fp)
                               #tt119 := #4 * #0
  addi $sp, $sp, -4
  li $t2, 0
  sw $t2, -148($fp)
                               #tt115 := vv4 + tt119
  lw $t0, 8($fp)
  lw $t1, -148($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -152($fp)
                               #tt109 := *tt110 * *tt115
  lw $t0, -144($fp)
  lw $t0, 0($t0)
  lw $t1, -152($fp)
  lw $t1, 0($t1)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -156($fp)
                               #tt97 := tt98 - tt109
  lw $t0, -136($fp)
  lw $t1, -156($fp)
  addi $sp, $sp, -4
  sub $t2, $t0, $t1
  sw $t2, -160($fp)
                               #*tt92 := tt97
  lw $t0, -116($fp)
  lw $t1, -160($fp)
  sw $t1, 0($t0)
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
                               #DEC vv6 24
  addi $sp, $sp, -24
                               #DEC vv7 12
  addi $sp, $sp, -12
                               #vv8 := #0
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -44($fp)
label1:
  addi $sp, $fp, -44
                               #IF vv8 >= #2 GOTO label3
  lw $t0, -44($fp)
  li $t1, 2
  bge $t0, $t1 label3
                               #vv9 := #0
  addi $sp, $sp, -4
  li $t0, 0
  sw $t0, -48($fp)
label4:
  addi $sp, $fp, -48
                               #IF vv9 >= #3 GOTO label6
  lw $t0, -48($fp)
  li $t1, 3
  bge $t0, $t1 label6
                               #tt135 := #12 * vv8
  lw $t1, -44($fp)
  addi $sp, $sp, -4
  li $t0, 12
  mul $t2, $t0, $t1
  sw $t2, -52($fp)
                               #tt131 := &vv6 + tt135
  addi $t0, $fp, -28
  lw $t1, -52($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -56($fp)
                               #tt137 := #4 * vv9
  lw $t1, -48($fp)
  addi $sp, $sp, -4
  li $t0, 4
  mul $t2, $t0, $t1
  sw $t2, -60($fp)
                               #tt129 := tt131 + tt137
  lw $t0, -56($fp)
  lw $t1, -60($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -64($fp)
                               #tt140 := vv8 + #1
  lw $t0, -44($fp)
  addi $sp, $sp, -4
  addi $t2, $t0, 1
  sw $t2, -68($fp)
                               #tt143 := vv8 + #1
  lw $t0, -44($fp)
  addi $sp, $sp, -4
  addi $t2, $t0, 1
  sw $t2, -72($fp)
                               #tt139 := tt140 * tt143
  lw $t0, -68($fp)
  lw $t1, -72($fp)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -76($fp)
                               #tt147 := vv9 + #1
  lw $t0, -48($fp)
  addi $sp, $sp, -4
  addi $t2, $t0, 1
  sw $t2, -80($fp)
                               #tt150 := vv9 + #1
  lw $t0, -48($fp)
  addi $sp, $sp, -4
  addi $t2, $t0, 1
  sw $t2, -84($fp)
                               #tt146 := tt147 * tt150
  lw $t0, -80($fp)
  lw $t1, -84($fp)
  addi $sp, $sp, -4
  mul $t2, $t0, $t1
  sw $t2, -88($fp)
                               #tt138 := tt139 + tt146
  lw $t0, -76($fp)
  lw $t1, -88($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -92($fp)
                               #*tt129 := tt138
  lw $t0, -64($fp)
  lw $t1, -92($fp)
  sw $t1, 0($t0)
                               #tt154 := vv9 + #1
  lw $t0, -48($fp)
  addi $sp, $sp, -4
  addi $t2, $t0, 1
  sw $t2, -96($fp)
                               #vv9 := tt154
  lw $t1, -96($fp)
  move $t0, $t1
  sw $t0, -48($fp)
                               #GOTO label4
  j label4
label6:
  addi $sp, $fp, -96
                               #tt158 := vv8 + #1
  lw $t0, -44($fp)
  addi $sp, $sp, -4
  addi $t2, $t0, 1
  sw $t2, -100($fp)
                               #vv8 := tt158
  lw $t1, -100($fp)
  move $t0, $t1
  sw $t0, -44($fp)
                               #GOTO label1
  j label1
label3:
  addi $sp, $fp, -100
                               #tt167 := #12 * #1
  addi $sp, $sp, -4
  li $t2, 12
  sw $t2, -104($fp)
                               #tt163 := &vv6 + tt167
  addi $t0, $fp, -28
  lw $t1, -104($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -108($fp)
                               #tt172 := #12 * #0
  addi $sp, $sp, -4
  li $t2, 0
  sw $t2, -112($fp)
                               #tt168 := &vv6 + tt172
  addi $t0, $fp, -28
  lw $t1, -112($fp)
  addi $sp, $sp, -4
  add $t2, $t0, $t1
  sw $t2, -116($fp)
                               #ARG &vv7
  addi $t0, $fp, -40
  addi $sp, $sp, -4
  sw $t0, -120($fp)
                               #ARG tt163
  lw $t0, -108($fp)
  addi $sp, $sp, -4
  sw $t0, -124($fp)
                               #ARG tt168
  lw $t0, -116($fp)
  addi $sp, $sp, -4
  sw $t0, -128($fp)
                               #tt161 := CALL cross_product
  jal cross_product
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  addi $sp, $sp, -4
  move $t0, $v0
  sw $t0, -132($fp)
                               #ARG &vv7
  addi $t0, $fp, -40
  addi $sp, $sp, -4
  sw $t0, -136($fp)
                               #ARG &vv7
  addi $t0, $fp, -40
  addi $sp, $sp, -4
  sw $t0, -140($fp)
                               #tt174 := CALL dot_product
  jal dot_product
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  addi $sp, $sp, -4
  move $t0, $v0
  sw $t0, -144($fp)
                               #WRITE tt174
  lw $t0, -144($fp)
  move $a0, $t0
  jal write
                               #RETURN #0
  li $v0, 0
  lw $ra, -4($fp)
  jr $ra
