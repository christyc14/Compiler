.text
.align 2
.globl f
f:
addiu  $sp,$sp,-32
sw  $31,28($sp)
sw $fp,24($sp)
move  $fp,$sp
jal g
nop
move  $sp,$fp
lw  $31,28($sp)
lw  $fp,24($sp)
addiu  $sp,$sp,32
j  $31
nop
