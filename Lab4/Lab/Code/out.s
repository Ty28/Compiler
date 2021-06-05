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

main:
  addi $sp, $sp, -4
  li $t0, 1
  sw $t0, -4($fp)
  addi $sp, $sp, -4
  li $t1, 2
  sw $t1, -8($fp)
  addi $sp, $sp, -4
  li $t2, 3
  sw $t2, -12($fp)
  lw $t4, -12($fp)
  move $t3, $t4
  sw $t3, -4($fp)
