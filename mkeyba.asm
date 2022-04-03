I_GR group I_ASMTEXT, I_TEXT, I_AUXTEXT

I_ASMTEXT SEGMENT BYTE PUBLIC 'INIT'

ASSUME CS:I_ASMTEXT

public _int2f_handler,_OldInt2F
public _int15_handler,_OldInt15

; SEGMENT_START:

_int2f_handler:
	cmp ax,0ad82h
	jne int2f_1
	mov [cs:_usebiosonly_flag],bl
	iret

int2f_1:
	cmp ax,0ad83h
	jne chain_int2f
	mov bl,[cs:_usebiosonly_flag]
	iret

chain_int2f:
	db 0eah		; Jump Far
_OldInt2F  	dd 0


extrn  _cint15_handler_full:near

_int15_handler:
	jnc chain_int15_non_carry

	cmp ah,04fh
	jne chain_int15

	push bx
	push cx
	push dx
	push ds
	push es

	push cs
	pop  ds
	push ax

	call _cint15_handler_full
	pop cx						; pop argument from stack

	pop es
	pop ds
	pop dx
	pop cx
	pop bx

						; scancode if pass down key to BIOS
						; 0  if scancode was handled
	mov ah,04fh
	cmp al,0
	jne chain_int15

;	clc       					; no good idea, as the win2K
;	sti							; DOS box behaves erratically
;	ret2

	push bp
	mov  bp,sp
	and  byte ptr [bp+6],0feh		; clear carry
	pop bp
	iret

chain_int15:
	stc
chain_int15_non_carry:
	db 0eah		; Jump Far
_OldInt15  	dd 0

;extern uchar usebiosonly_flag;
;extern uchar debug_scancode;
;extern uint  RESIDENT currentCombi             ;
;extern uchar RESIDENT currentCombiScancode     ;
;extern uint  RESIDENT ResidentCombiTables[5]   ;
;extern uchar RESIDENT DecimalDingsBums         ;    /* grey , or . */
;extern char  *ResidentScancodetable;

public _OldInt9
public _OldInt16

public _usebiosonly_flag
public _lastisctrl_flag

public _debug_scancode,_currentCombi
public _ResidentCombiTables, _DecimalDingsBums,_SilentKeyboard
public _pResidentScancodetable
extrn _ResidentScancodetable

_OldInt9 dd 0
_OldInt16 dd 0
_usebiosonly_flag db 0ffh
_lastisctrl_flag db 0
_debug_scancode   db 0
_currentCombi     dw 0
_DecimalDingsBums    db 0
_SilentKeyboard   db 0
_ResidentCombiTables dw 0,0,0,0,0,0
_pResidentScancodetable dw 0

I_ASMTEXT ENDS

I_TEXT SEGMENT BYTE PUBLIC 'INIT'
; cint15_handler_* routines are here
I_TEXT ENDS

I_AUXTEXT SEGMENT BYTE PUBLIC 'INIT'

public _int9_handler
public _int16_handler,_END_int16_handler

ASSUME CS:I_GR

; Optional handlers for INT9 and INT16
_int9_handler:
	jmp int9_start			; Workaround for APL software
int9_isActiveF dw 1    		; Modified by APL software
int9_start:
	; save the registers
	push ax        		; scancode
	; compute if we should handle the extended
	mov al, byte ptr [cs:int9_isActiveF]
	or al, al
	jz chain_int9
	; read and authenticate scancode
	in al, 60h		; get the scancode in AL
	mov ah, 4fh		; authenticate scancode
	stc

	int 15h			; return: CF clear if no further processing
	jc chain_int9
	; clear keyboard buffer
	in al, 61h		; read status register
	or al, 080h		; set bit 7
	out 61h, al
	and al, 7fh		; clear bit 7
	out 61h, al
	; report end of interrupt to interrupt controller
	mov al, 20h
	out 20h, al
	jmp leave_int9
chain_int9:
	pushf
	call [cs:_OldInt9]
	; leave interrupt routine
leave_int9:
	pop ax
	iret

_int16_handler:
	cmp ah, 05 		; check INT 16 function number
	jne chain_int16		; call old handler if != 05
	; save registers
	push di
	push ds
	mov di, 040h
	mov ds, di
	mov di, [ds:001Ch]
	mov [di], cx
	add di, 2
	cmp di, [ds:0082h]
	jne int16_1
	mov di,[ds:0080h]
int16_1:
	cmp di,[ds:001Ah]
	je int16_2
	mov [ds:001Ch], di
	xor al, al
	jmp int16_3
int16_2:
	mov al,01
int16_3:
	pop ds
	pop di
	iret

chain_int16:
	jmp [cs:_OldInt16]

_END_int16_handler:
	nop

I_AUXTEXT ENDS


END




