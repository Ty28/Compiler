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
  addi $sp, $sp, -52
                               #PARAM vv1
                               #vv2 := #34
                               #tt7 := vv1 * vv2
                               #tt6 := tt7 - vv1
                               #tt11 := vv2 * vv1
                               #tt5 := tt6 + tt11
                               #tt14 := vv2 * vv2
                               #tt4 := tt5 + tt14
                               #tt3 := tt4 + #18
                               #vv2 := tt3
                               #tt21 := vv2 * #3
                               #tt24 := vv1 * #3
                               #tt20 := tt21 - tt24
                               #tt19 := tt20 + #335
                               #vv2 := tt19
                               #RETURN vv2
  addi $sp, $sp, -20
                               #PARAM vv3
                               #PARAM vv4
                               #tt32 := vv3 / vv4
                               #tt31 := tt32 * vv4
                               #tt29 := vv3 - tt31
                               #RETURN tt29
  addi $sp, $sp, -96
                               #vv5 := #5
                               #vv6 := #7
                               #vv7 := #11
                               #tt58 := vv5 + vv6
                               #vv8 := tt58
                               #tt62 := vv5 + vv6
                               #tt65 := vv7 / #1
                               #tt61 := tt62 + tt65
                               #vv9 := tt61
                               #tt69 := vv5 * vv6
                               #tt68 := tt69 - vv7
                               #vv10 := tt68
                               #vv11 := #42
                               #vv12 := #4
                               #vv13 := #0
                               #vv14 := #0
                               #DEC vv15 16
                               #tt81 := vv5 + vv6
                               #tt80 := tt81 + vv7
                               #tt79 := tt80 + #1500
                               #tt78 := tt79 - vv10
                               #vv10 := tt78
                               #IF vv13 >= #4 GOTO label3
                               #tt90 := #15 * vv13
  addi $sp, $sp, -16
                               #vv14 := tt90
                               #tt97 := #4 * vv13
                               #tt93 := &vv15 + tt97
                               #*tt93 := vv14
                               #tt100 := vv13 + #1
                               #vv13 := tt100
                               #GOTO label1
                               #IF vv13 >= #7 GOTO label6
                               #WRITE vv10
  addi $sp, $sp, -12
                               #ARG #2
                               #ARG vv10
                               #tt107 := CALL mod
                               #IF tt107 <= #0 GOTO label8
                               #tt112 := vv13 - #1
  addi $sp, $sp, -8
                               #vv16 := tt112
  addi $sp, $sp, -28
                               #ARG vv5
                               #tt115 := CALL process
                               #tt120 := vv5 + #3
                               #tt119 := tt120 - #2
                               #tt118 := tt119 - #1
                               #ARG tt118
                               #tt116 := CALL process
                               #IF tt115 != tt116 GOTO label10
                               #tt127 := vv10 - #2
  addi $sp, $sp, -8
                               #tt126 := tt127 + #1
                               #vv10 := tt126
  addi $sp, $sp, -16
                               #tt133 := vv5 + #2
                               #tt132 := tt133 + #1
                               #vv5 := tt132
                               #tt138 := vv13 + #1
                               #vv13 := tt138
                               #tt142 := vv13 + #1
                               #vv13 := tt142
                               #GOTO label3
  addi $sp, $sp, -32
                               #tt150 := #4 * #0
                               #tt146 := &vv15 + tt150
                               #WRITE *tt146
                               #tt156 := #4 * #1
                               #tt152 := &vv15 + tt156
                               #WRITE *tt152
                               #tt162 := #4 * #2
                               #tt158 := &vv15 + tt162
                               #WRITE *tt158
                               #tt168 := #4 * #3
                               #tt164 := &vv15 + tt168
                               #WRITE *tt164
                               #RETURN #0
