.intel_syntax noprefix
.code16

.section .fartext._0

.globl int2f_handler,OldInt2F
.globl int15_handler,OldInt15

# SEGMENT_START:

int2f_handler:
	cmp ax, 0x0ad80
	jne int2f_82
	mov ax, MY_INSTALL_SIGNATURE	# Report mKEYB installed
	mov bx, MY_VERSION_SIGNATURE	# BH is major BL is minor version
	mov di, cs
	mov es, di
	mov di, offset OldInt9			# ES:DI points to data block
	iret

int2f_82:
	cmp ax, 0x0ad82
	jne int2f_83
	mov [cs:usebiosonly_flag],bl
	iret

int2f_83:
	cmp ax, 0x0ad83
	jne chain_int2f
	mov bl,[cs:usebiosonly_flag]
	iret

chain_int2f:
	.byte 0xea		# Jump Far
OldInt2F:  	.word 0, 0


.globl  cint15_handler_full

int15_handler:
	jnc chain_int15_non_carry

	cmp ah, 0x04f
	jne chain_int15

	push bx
	push cx
	push dx
	push ds
	push es

	push cs
	pop  ds
	push ax                     # push argument to stack
	call cint15_handler_full
	pop cx						# pop argument from stack

	pop es
	pop ds
	pop dx
	pop cx
	pop bx

						# scancode if pass down key to BIOS
						# 0  if scancode was handled
	mov ah, 0x04f
	cmp al,0
	jne chain_int15

#	clc       					# no good idea, as the win2K
#	sti							# DOS box behaves erratically
#	ret2

	push bp
	mov  bp,sp
	and  byte ptr [bp+6], 0x0fe		# clear carry
	pop bp
	iret

chain_int15:
	stc
chain_int15_non_carry:
	.byte 0xea		# Jump Far
OldInt15:  	.word 0,0

#extern uchar usebiosonly_flag#
#extern uchar debug_scancode#
#extern uint  RESIDENT currentCombi             #
#extern uchar RESIDENT currentCombiScancode     #
#extern uint  RESIDENT ResidentCombiTables[5]   #
#extern uchar RESIDENT DecimalDingsBums         #    /* grey , or . */
#extern char  *ResidentScancodetable#

.globl OldInt9
.globl OldInt16

.globl usebiosonly_flag
.globl Flags

.globl debug_scancode, currentCombi
.globl ResidentCombiTables, DecimalDingsBums
.globl pResidentScancodetable
#extrn ResidentScancodetable

OldInt9:                .word 0,0
OldInt16:               .word 0,0
usebiosonly_flag:       .byte 0x0ff
Flags: 			.byte 0
debug_scancode:         .byte 0
currentCombi:           .word 0
DecimalDingsBums:       .byte 0
ResidentCombiTables:    .word 0,0,0,0,0,0
pResidentScancodetable: .word 0
