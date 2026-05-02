.intel_syntax noprefix
.code16

.section .fartext._2


.globl int9_handler
.globl int16_handler, END_int16_handler

    #  ? ASSUME CS:I_GROUP

# Optional handlers for INT9 and INT16
int9_handler:
	jmp int9_start			# Workaround for APL software
int9_isActiveF: .word 1    		# Modified by APL software
int9_start:
	# save the registers
	push ax        		# scancode
	# compute if we should handle the extended
	mov al, byte ptr [cs:int9_isActiveF]
	or al, al
	jz chain_int9
	# read and authenticate scancode
	in al, 0x60		# get the scancode in AL
	mov ah, 0x4f		# authenticate scancode
	stc

	int 0x15			# return: CF clear if no further processing
	jc chain_int9
	# clear keyboard buffer
	in al, 0x61		# read status register
	or al, 0x80		# set bit 7
	out 0x61, al
	and al, 0x7f		# clear bit 7
	out 0x61, al
	# report end of interrupt to interrupt controller
	mov al, 0x20
	out 0x20, al
	jmp leave_int9
chain_int9:
	pushf
	call dword ptr [cs:OldInt9]
	# leave interrupt routine
leave_int9:
	pop ax
	iret

int16_handler:
	cmp ah, 05 		# check INT 16 function number
	jne chain_int16		# call old handler if != 05
	# save registers
	push di
	push ds
	mov di, 0x040
	mov ds, di
	mov di, [ds:0x001C]
	mov [di], cx
	add di, 2
	cmp di, [ds:0x0082]
	jne int16_1
	mov di,[ds:0x0080]
int16_1:
	cmp di,[ds:0x001]
	je int16_2
	mov [ds:0x001C], di
	xor al, al
	jmp int16_3
int16_2:
	mov al,01
int16_3:
	pop ds
	pop di
	iret

chain_int16:
	jmp dword ptr [cs:OldInt16]

END_int16_handler:
	nop
