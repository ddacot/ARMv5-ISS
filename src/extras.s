@ -------------------------------------------
@ File: armos_asm.s
@ Desc: Defines ARM vector table and assembly routines
@       for exception handling
@ -------------------------------------------

.text
.global _start
_start:

.org 0x1000
@ -------------------------------------------
@ UHSUB 16
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uhsub16 r1,r2,r3
cmp r1, #0
@if true, Z flag will be set

@ -------------------------------------------
@ UHSUB 8
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uhsub8 r1,r2,r3
cmp r1, #0
@if true, Z flag will be set

@ -------------------------------------------
@ UHADDSUBX
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uhaddsubx r1,r2,r3
cmp r1, #0
@if true, Z flag will be set

@ -------------------------------------------
@ UHADD 16
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uhadd16 r1,r2,r3
cmp r1, #0
@if true, Z flag will be set

@ -------------------------------------------
@ UHADD 8
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uhadd8 r1,r2,r3
cmp r1, #0
@if true, Z flag will be set

@ -------------------------------------------
@ UXTAB 16
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uxtab16 r1,r2,r3
cmp r1, #0
@if true, Z flag will be set

@ -------------------------------------------
@ UXTAB 
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uxtab r1,r3,r2
cmp r1, #0
@if true, Z flag will be set

@ -------------------------------------------
@ UXTAH
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uxtah r1,r3,r2
cmp r1, #0
@if true, Z flag will be set

@ -------------------------------------------
@ UXTB 16
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uxtb16 r1, r2
cmp r1, #0
@if true, Z flag will be set

@ -------------------------------------------
@ UXTB 8
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uxtb16 r1, r2
cmp r1, #0
@if true, Z flag will be set

@ -------------------------------------------
@ UXTH
@ -------------------------------------------

mov r2, #0xFFFFFFFF
uxth r1, r2
cmp r1, #0
@if true, Z flag will be set





    