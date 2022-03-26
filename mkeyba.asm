group   I_GR I_ASMTEXT
segment I_ASMTEXT class=INIT align=1


global _int2f_handler,_OldInt2F
global _int15_handler,_OldInt15

SEGMENT_START:


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


                extern  _cint15_handler_full

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

	call near _cint15_handler_full
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
	and  byte [bp+6],0feh		; clear carry
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


global _usebiosonly_flag
global _lastisctrl_flag

global _debug_scancode,_currentCombi
global _ResidentCombiTables, _DecimalDingsBums,_SilentKeyboard
global _pResidentScancodetable
extern _ResidentScancodetable


_usebiosonly_flag db 0ffh
_lastisctrl_flag db 0
_debug_scancode   db 0
_currentCombi     dw 0
_DecimalDingsBums    db 0
_SilentKeyboard   db 0
_ResidentCombiTables dw 0,0,0,0,0,0
_pResidentScancodetable dw 0






