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
  addi $sp, $sp, -128
                               #PARAM vv1    0
                               #vv2 := #4    0
  li $t0, 4
  sw $t0, -8($fp)
                               #tt3 := vv1 + #12    0
  lw $t0, 8($fp)
  li $t1, 12
  add $t2, $t0, $t1
  sw $t2, -12($fp)
                               #vv3 := tt3    0
  lw $t1, -12($fp)
  move $t0, $t1
  sw $t0, -16($fp)
                               #tt7 := vv1 + #12    0
  lw $t0, 8($fp)
  li $t1, 12
  add $t2, $t0, $t1
  sw $t2, -20($fp)
                               #vv3 := tt7    0
  lw $t1, -20($fp)
  move $t0, $t1
  sw $t0, -16($fp)
                               #vv2 := vv2    0
  lw $t1, -8($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #tt14 := vv2 + #0    0
  lw $t0, -8($fp)
  li $t1, 0
  add $t2, $t0, $t1
  sw $t2, -24($fp)
                               #tt13 := tt14 - #0    0
  lw $t0, -24($fp)
  li $t1, 0
  sub $t2, $t0, $t1
  sw $t2, -28($fp)
                               #vv2 := tt13    0
  lw $t1, -28($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #tt20 := vv2 * #1    0
  lw $t0, -8($fp)
  li $t1, 1
  mul $t2, $t0, $t1
  sw $t2, -32($fp)
                               #tt19 := tt20 / #1    0
  lw $t0, -32($fp)
  li $t1, 1
  div $t0, $t1
  mflo $t2
  sw $t2, -36($fp)
                               #vv2 := tt19    0
  lw $t1, -36($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #tt26 := vv2 + #32    0
  lw $t0, -8($fp)
  li $t1, 32
  add $t2, $t0, $t1
  sw $t2, -40($fp)
                               #tt25 := tt26 - #2    0
  lw $t0, -40($fp)
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -44($fp)
                               #vv2 := tt25    0
  lw $t1, -44($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #tt43 := vv1 * vv2    0
  lw $t0, 8($fp)
  lw $t1, -8($fp)
  mul $t2, $t0, $t1
  sw $t2, -48($fp)
                               #tt46 := vv1 * vv2    0
  lw $t0, 8($fp)
  lw $t1, -8($fp)
  mul $t2, $t0, $t1
  sw $t2, -52($fp)
                               #tt42 := tt43 + tt46    0
  lw $t0, -48($fp)
  lw $t1, -52($fp)
  add $t2, $t0, $t1
  sw $t2, -56($fp)
                               #tt49 := vv2 * vv1    0
  lw $t0, -8($fp)
  lw $t1, 8($fp)
  mul $t2, $t0, $t1
  sw $t2, -60($fp)
                               #tt41 := tt42 - tt49    0
  lw $t0, -56($fp)
  lw $t1, -60($fp)
  sub $t2, $t0, $t1
  sw $t2, -64($fp)
                               #tt40 := tt41 - vv1    0
  lw $t0, -64($fp)
  lw $t1, 8($fp)
  sub $t2, $t0, $t1
  sw $t2, -68($fp)
                               #tt53 := vv2 * vv1    0
  lw $t0, -8($fp)
  lw $t1, 8($fp)
  mul $t2, $t0, $t1
  sw $t2, -72($fp)
                               #tt39 := tt40 + tt53    0
  lw $t0, -68($fp)
  lw $t1, -72($fp)
  add $t2, $t0, $t1
  sw $t2, -76($fp)
                               #tt56 := vv2 * vv2    0
  lw $t0, -8($fp)
  lw $t1, -8($fp)
  mul $t2, $t0, $t1
  sw $t2, -80($fp)
                               #tt38 := tt39 + tt56    0
  lw $t0, -76($fp)
  lw $t1, -80($fp)
  add $t2, $t0, $t1
  sw $t2, -84($fp)
                               #tt59 := vv1 / vv1    0
  lw $t0, 8($fp)
  lw $t1, 8($fp)
  div $t0, $t1
  mflo $t2
  sw $t2, -88($fp)
                               #tt37 := tt38 + tt59    0
  lw $t0, -84($fp)
  lw $t1, -88($fp)
  add $t2, $t0, $t1
  sw $t2, -92($fp)
                               #tt36 := tt37 - #12    0
  lw $t0, -92($fp)
  li $t1, 12
  sub $t2, $t0, $t1
  sw $t2, -96($fp)
                               #tt35 := tt36 + #29    0
  lw $t0, -96($fp)
  li $t1, 29
  add $t2, $t0, $t1
  sw $t2, -100($fp)
                               #vv2 := tt35    0
  lw $t1, -100($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #tt72 := vv2 * #3    0
  lw $t0, -8($fp)
  li $t1, 3
  mul $t2, $t0, $t1
  sw $t2, -104($fp)
                               #tt71 := tt72 + #336    0
  lw $t0, -104($fp)
  li $t1, 336
  add $t2, $t0, $t1
  sw $t2, -108($fp)
                               #tt79 := vv1 * #12    0
  lw $t0, 8($fp)
  li $t1, 12
  mul $t2, $t0, $t1
  sw $t2, -112($fp)
                               #tt78 := tt79 / #4    0
  lw $t0, -112($fp)
  li $t1, 4
  div $t0, $t1
  mflo $t2
  sw $t2, -116($fp)
                               #tt70 := tt71 - tt78    0
  lw $t0, -108($fp)
  lw $t1, -116($fp)
  sub $t2, $t0, $t1
  sw $t2, -120($fp)
                               #tt69 := tt70 + #20    0
  lw $t0, -120($fp)
  li $t1, 20
  add $t2, $t0, $t1
  sw $t2, -124($fp)
                               #tt68 := tt69 - #20    0
  lw $t0, -124($fp)
  li $t1, 20
  sub $t2, $t0, $t1
  sw $t2, -128($fp)
                               #tt67 := tt68 - #0    0
  lw $t0, -128($fp)
  li $t1, 0
  sub $t2, $t0, $t1
  sw $t2, -132($fp)
                               #vv2 := tt67    0
  lw $t1, -132($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #RETURN vv2    0
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
  addi $sp, $sp, -12
                               #PARAM vv4    0
                               #PARAM vv5    0
                               #tt96 := vv4 / vv5    0
  lw $t0, 8($fp)
  lw $t1, 12($fp)
  div $t0, $t1
  mflo $t2
  sw $t2, -8($fp)
                               #tt95 := tt96 * vv5    0
  lw $t0, -8($fp)
  lw $t1, 12($fp)
  mul $t2, $t0, $t1
  sw $t2, -12($fp)
                               #tt93 := vv4 - tt95    0
  lw $t0, 8($fp)
  lw $t1, -12($fp)
  sub $t2, $t0, $t1
  sw $t2, -16($fp)
                               #RETURN tt93    0
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
  addi $sp, $sp, -340
                               #vv6 := #5    0
  li $t0, 5
  sw $t0, -8($fp)
                               #vv7 := #7    0
  li $t0, 7
  sw $t0, -12($fp)
                               #vv8 := #11    0
  li $t0, 11
  sw $t0, -16($fp)
                               #tt122 := vv6 + vv7    0
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  add $t2, $t0, $t1
  sw $t2, -20($fp)
                               #vv9 := tt122    0
  lw $t1, -20($fp)
  move $t0, $t1
  sw $t0, -24($fp)
                               #tt126 := vv6 + vv7    0
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  add $t2, $t0, $t1
  sw $t2, -28($fp)
                               #tt129 := vv8 / #1    0
  lw $t0, -16($fp)
  li $t1, 1
  div $t0, $t1
  mflo $t2
  sw $t2, -32($fp)
                               #tt125 := tt126 + tt129    0
  lw $t0, -28($fp)
  lw $t1, -32($fp)
  add $t2, $t0, $t1
  sw $t2, -36($fp)
                               #vv10 := tt125    0
  lw $t1, -36($fp)
  move $t0, $t1
  sw $t0, -40($fp)
                               #tt133 := vv6 * vv7    0
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  mul $t2, $t0, $t1
  sw $t2, -44($fp)
                               #tt132 := tt133 - vv8    0
  lw $t0, -44($fp)
  lw $t1, -16($fp)
  sub $t2, $t0, $t1
  sw $t2, -48($fp)
                               #vv11 := tt132    0
  lw $t1, -48($fp)
  move $t0, $t1
  sw $t0, -52($fp)
                               #vv12 := #42    0
  li $t0, 42
  sw $t0, -56($fp)
                               #vv13 := #4    0
  li $t0, 4
  sw $t0, -60($fp)
                               #vv14 := #0    0
  li $t0, 0
  sw $t0, -64($fp)
                               #vv15 := #0    0
  li $t0, 0
  sw $t0, -68($fp)
                               #DEC vv16 16    0
                               #tt145 := vv6 + vv7    0
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  add $t2, $t0, $t1
  sw $t2, -88($fp)
                               #tt144 := tt145 + vv8    0
  lw $t0, -88($fp)
  lw $t1, -16($fp)
  add $t2, $t0, $t1
  sw $t2, -92($fp)
                               #tt143 := tt144 + #1500    0
  lw $t0, -92($fp)
  li $t1, 1500
  add $t2, $t0, $t1
  sw $t2, -96($fp)
                               #tt142 := tt143 - vv11    0
  lw $t0, -96($fp)
  lw $t1, -52($fp)
  sub $t2, $t0, $t1
  sw $t2, -100($fp)
                               #vv11 := tt142    0
  lw $t1, -100($fp)
  move $t0, $t1
  sw $t0, -52($fp)
                               #LABEL label1 :    1
label1:
                               #IF vv14 >= #4 GOTO label3    0
  lw $t0, -64($fp)
  li $t1, 4
  bge $t0, $t1 label3
                               #tt154 := #15 * vv14    1
  lw $t1, -64($fp)
  li $t0, 15
  mul $t2, $t0, $t1
  sw $t2, -104($fp)
                               #vv15 := tt154    0
  lw $t1, -104($fp)
  move $t0, $t1
  sw $t0, -68($fp)
                               #tt161 := #4 * vv14    0
  lw $t1, -64($fp)
  li $t0, 4
  mul $t2, $t0, $t1
  sw $t2, -108($fp)
                               #tt157 := &vv16 + tt161    0
  addi $t0, $fp, -84
  lw $t1, -108($fp)
  add $t2, $t0, $t1
  sw $t2, -112($fp)
                               #*tt157 := vv15    0
  lw $t0, -112($fp)
  lw $t1, -68($fp)
  sw $t1, 0($t0)
                               #tt164 := vv14 + #1    0
  lw $t0, -64($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -116($fp)
                               #vv14 := tt164    0
  lw $t1, -116($fp)
  move $t0, $t1
  sw $t0, -64($fp)
                               #GOTO label1    0
  j label1
                               #LABEL label3 :    1
label3:
                               #IF vv14 >= vv11 GOTO label6    0
  lw $t0, -64($fp)
  lw $t1, -52($fp)
  bge $t0, $t1 label6
                               #tt170 := vv13 * vv13    1
  lw $t0, -60($fp)
  lw $t1, -60($fp)
  mul $t2, $t0, $t1
  sw $t2, -120($fp)
                               #vv17 := tt170    0
  lw $t1, -120($fp)
  move $t0, $t1
  sw $t0, -124($fp)
                               #tt178 := vv12 + vv17    0
  lw $t0, -56($fp)
  lw $t1, -124($fp)
  add $t2, $t0, $t1
  sw $t2, -128($fp)
                               #tt181 := vv14 * #12    0
  lw $t0, -64($fp)
  li $t1, 12
  mul $t2, $t0, $t1
  sw $t2, -132($fp)
                               #tt177 := tt178 + tt181    0
  lw $t0, -128($fp)
  lw $t1, -132($fp)
  add $t2, $t0, $t1
  sw $t2, -136($fp)
                               #tt184 := #4 * vv13    0
  lw $t1, -60($fp)
  li $t0, 4
  mul $t2, $t0, $t1
  sw $t2, -140($fp)
                               #tt176 := tt177 - tt184    0
  lw $t0, -136($fp)
  lw $t1, -140($fp)
  sub $t2, $t0, $t1
  sw $t2, -144($fp)
                               #tt175 := tt176 + #5    0
  lw $t0, -144($fp)
  li $t1, 5
  add $t2, $t0, $t1
  sw $t2, -148($fp)
                               #tt174 := tt175 + #2    0
  lw $t0, -148($fp)
  li $t1, 2
  add $t2, $t0, $t1
  sw $t2, -152($fp)
                               #vv12 := tt174    0
  lw $t1, -152($fp)
  move $t0, $t1
  sw $t0, -56($fp)
                               #ARG vv11    1
  lw $t0, -52($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #tt195 := CALL process    1
  addi $sp, $sp, -4
  jal process
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  move $t0, $v0
  sw $t0, -156($fp)
                               #tt197 := #2 * vv6    1
  lw $t1, -8($fp)
  li $t0, 2
  mul $t2, $t0, $t1
  sw $t2, -160($fp)
                               #tt194 := tt195 + tt197    0
  lw $t0, -156($fp)
  lw $t1, -160($fp)
  add $t2, $t0, $t1
  sw $t2, -164($fp)
                               #tt193 := tt194 - vv11    0
  lw $t0, -164($fp)
  lw $t1, -52($fp)
  sub $t2, $t0, $t1
  sw $t2, -168($fp)
                               #tt201 := vv8 * vv9    0
  lw $t0, -16($fp)
  lw $t1, -24($fp)
  mul $t2, $t0, $t1
  sw $t2, -172($fp)
                               #tt192 := tt193 + tt201    0
  lw $t0, -168($fp)
  lw $t1, -172($fp)
  add $t2, $t0, $t1
  sw $t2, -176($fp)
                               #vv18 := tt192    0
  lw $t1, -176($fp)
  move $t0, $t1
  sw $t0, -180($fp)
                               #ARG #2    1
  li $t0, 2
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG vv11    0
  lw $t0, -52($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #tt204 := CALL mod    1
  addi $sp, $sp, -4
  jal mod
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  move $t0, $v0
  sw $t0, -184($fp)
                               #IF tt204 <= #0 GOTO label8    1
  lw $t0, -184($fp)
  li $t1, 0
  ble $t0, $t1 label8
                               #tt209 := vv14 + #3    1
  lw $t0, -64($fp)
  li $t1, 3
  add $t2, $t0, $t1
  sw $t2, -188($fp)
                               #vv19 := tt209    0
  lw $t1, -188($fp)
  move $t0, $t1
  sw $t0, -192($fp)
                               #tt213 := vv19 - #1    0
  lw $t0, -192($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -196($fp)
                               #vv19 := tt213    0
  lw $t1, -196($fp)
  move $t0, $t1
  sw $t0, -192($fp)
                               #tt217 := vv19 + #3    0
  lw $t0, -192($fp)
  li $t1, 3
  add $t2, $t0, $t1
  sw $t2, -200($fp)
                               #vv19 := tt217    0
  lw $t1, -200($fp)
  move $t0, $t1
  sw $t0, -192($fp)
                               #tt221 := vv19 - #6    0
  lw $t0, -192($fp)
  li $t1, 6
  sub $t2, $t0, $t1
  sw $t2, -204($fp)
                               #vv19 := tt221    0
  lw $t1, -204($fp)
  move $t0, $t1
  sw $t0, -192($fp)
                               #LABEL label8 :    1
label8:
                               #ARG vv6    1
  lw $t0, -8($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #tt226 := CALL process    1
  addi $sp, $sp, -4
  jal process
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  move $t0, $v0
  sw $t0, -208($fp)
                               #tt231 := vv6 + #3    1
  lw $t0, -8($fp)
  li $t1, 3
  add $t2, $t0, $t1
  sw $t2, -212($fp)
                               #tt230 := tt231 - #2    0
  lw $t0, -212($fp)
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -216($fp)
                               #tt229 := tt230 - #1    0
  lw $t0, -216($fp)
  li $t1, 1
  sub $t2, $t0, $t1
  sw $t2, -220($fp)
                               #ARG tt229    1
  lw $t0, -220($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #tt227 := CALL process    1
  addi $sp, $sp, -4
  jal process
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  move $t0, $v0
  sw $t0, -224($fp)
                               #IF tt226 != tt227 GOTO label10    1
  lw $t0, -208($fp)
  lw $t1, -224($fp)
  bne $t0, $t1 label10
                               #tt238 := vv11 - #2    1
  lw $t0, -52($fp)
  li $t1, 2
  sub $t2, $t0, $t1
  sw $t2, -228($fp)
                               #tt237 := tt238 + #1    0
  lw $t0, -228($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -232($fp)
                               #vv11 := tt237    0
  lw $t1, -232($fp)
  move $t0, $t1
  sw $t0, -52($fp)
                               #ARG #4    1
  li $t0, 4
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG vv11    0
  lw $t0, -52($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #tt243 := CALL mod    1
  addi $sp, $sp, -4
  jal mod
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  move $t0, $v0
  sw $t0, -236($fp)
                               #tt248 := #4 * tt243    1
  lw $t1, -236($fp)
  li $t0, 4
  mul $t2, $t0, $t1
  sw $t2, -240($fp)
                               #tt242 := &vv16 + tt248    0
  addi $t0, $fp, -84
  lw $t1, -240($fp)
  add $t2, $t0, $t1
  sw $t2, -244($fp)
                               #ARG #4    1
  li $t0, 4
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #ARG vv11    0
  lw $t0, -52($fp)
  addi $sp, $sp, -4
  sw $t0, 0($sp)
                               #tt253 := CALL mod    1
  addi $sp, $sp, -4
  jal mod
  addi $sp, $fp, 4
  lw $fp, 0($fp)
  move $t0, $v0
  sw $t0, -248($fp)
                               #tt258 := #4 * tt253    1
  lw $t1, -248($fp)
  li $t0, 4
  mul $t2, $t0, $t1
  sw $t2, -252($fp)
                               #tt252 := &vv16 + tt258    0
  addi $t0, $fp, -84
  lw $t1, -252($fp)
  add $t2, $t0, $t1
  sw $t2, -256($fp)
                               #tt251 := *tt252 + vv19    0
  lw $t0, -256($fp)
  lw $t0, 0($t0)
  lw $t1, -192($fp)
  add $t2, $t0, $t1
  sw $t2, -260($fp)
                               #tt250 := tt251 + vv18    0
  lw $t0, -260($fp)
  lw $t1, -180($fp)
  add $t2, $t0, $t1
  sw $t2, -264($fp)
                               #tt249 := tt250 - vv10    0
  lw $t0, -264($fp)
  lw $t1, -40($fp)
  sub $t2, $t0, $t1
  sw $t2, -268($fp)
                               #*tt242 := tt249    0
  lw $t0, -244($fp)
  lw $t1, -268($fp)
  sw $t1, 0($t0)
                               #LABEL label10 :    1
label10:
                               #tt264 := vv6 + #2    0
  lw $t0, -8($fp)
  li $t1, 2
  add $t2, $t0, $t1
  sw $t2, -272($fp)
                               #tt263 := tt264 + #1    0
  lw $t0, -272($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -276($fp)
                               #vv6 := tt263    0
  lw $t1, -276($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #tt269 := vv14 + #1    0
  lw $t0, -64($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -280($fp)
                               #vv14 := tt269    0
  lw $t1, -280($fp)
  move $t0, $t1
  sw $t0, -64($fp)
                               #tt273 := vv14 + #1    0
  lw $t0, -64($fp)
  li $t1, 1
  add $t2, $t0, $t1
  sw $t2, -284($fp)
                               #vv14 := tt273    0
  lw $t1, -284($fp)
  move $t0, $t1
  sw $t0, -64($fp)
                               #GOTO label3    0
  j label3
                               #LABEL label6 :    1
label6:
                               #tt277 := vv6 + vv7    0
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  add $t2, $t0, $t1
  sw $t2, -288($fp)
                               #vv6 := tt277    0
  lw $t1, -288($fp)
  move $t0, $t1
  sw $t0, -8($fp)
                               #tt281 := vv6 + vv7    0
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  add $t2, $t0, $t1
  sw $t2, -292($fp)
                               #vv7 := tt281    0
  lw $t1, -292($fp)
  move $t0, $t1
  sw $t0, -12($fp)
                               #tt285 := vv6 + vv7    0
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  add $t2, $t0, $t1
  sw $t2, -296($fp)
                               #vv8 := tt285    0
  lw $t1, -296($fp)
  move $t0, $t1
  sw $t0, -16($fp)
                               #tt289 := vv6 + vv7    0
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  add $t2, $t0, $t1
  sw $t2, -300($fp)
                               #vv11 := tt289    0
  lw $t1, -300($fp)
  move $t0, $t1
  sw $t0, -52($fp)
                               #tt293 := vv6 + vv7    0
  lw $t0, -8($fp)
  lw $t1, -12($fp)
  add $t2, $t0, $t1
  sw $t2, -304($fp)
                               #vv18 := tt293    0
  lw $t1, -304($fp)
  move $t0, $t1
  sw $t0, -180($fp)
                               #tt298 := vv8 + vv11    0
  lw $t0, -16($fp)
  lw $t1, -52($fp)
  add $t2, $t0, $t1
  sw $t2, -308($fp)
                               #tt297 := tt298 + vv18    0
  lw $t0, -308($fp)
  lw $t1, -180($fp)
  add $t2, $t0, $t1
  sw $t2, -312($fp)
                               #WRITE tt297    0
  lw $t0, -312($fp)
  move $a0, $t0
  jal write
                               #tt307 := #4 * #0    0
  li $t0, 4
  li $t1, 0
  mul $t2, $t0, $t1
  sw $t2, -316($fp)
                               #tt303 := &vv16 + tt307    0
  addi $t0, $fp, -84
  lw $t1, -316($fp)
  add $t2, $t0, $t1
  sw $t2, -320($fp)
                               #WRITE *tt303    0
  lw $t0, -320($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #tt313 := #4 * #1    0
  li $t0, 4
  li $t1, 1
  mul $t2, $t0, $t1
  sw $t2, -324($fp)
                               #tt309 := &vv16 + tt313    0
  addi $t0, $fp, -84
  lw $t1, -324($fp)
  add $t2, $t0, $t1
  sw $t2, -328($fp)
                               #WRITE *tt309    0
  lw $t0, -328($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #tt319 := #4 * #2    0
  li $t0, 4
  li $t1, 2
  mul $t2, $t0, $t1
  sw $t2, -332($fp)
                               #tt315 := &vv16 + tt319    0
  addi $t0, $fp, -84
  lw $t1, -332($fp)
  add $t2, $t0, $t1
  sw $t2, -336($fp)
                               #WRITE *tt315    0
  lw $t0, -336($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #tt325 := #4 * #3    0
  li $t0, 4
  li $t1, 3
  mul $t2, $t0, $t1
  sw $t2, -340($fp)
                               #tt321 := &vv16 + tt325    0
  addi $t0, $fp, -84
  lw $t1, -340($fp)
  add $t2, $t0, $t1
  sw $t2, -344($fp)
                               #WRITE *tt321    0
  lw $t0, -344($fp)
  lw $t0, 0($t0)
  move $a0, $t0
  jal write
                               #RETURN #0    0
  li $v0, 0
  lw $ra, -4($fp)
  jr $ra
