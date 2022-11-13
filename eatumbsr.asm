I_GROUP group I_ASMTEXT

I_ASMTEXT SEGMENT PARA PUBLIC 'INIT'

ASSUME CS:I_ASMTEXT

public int2d_handler_,_OldInt2D,END_int2d_handler_

; SEGMENT_START:
TSR_Sig   byte 'eatUMBS '
TSR_Ver   dw        (1 SHL 8) + 0    ; (minor shl 8) + major
MPlex     db        028h             ; multiplex ID

int2d_handler_:
    cmp       ah, cs:MPlex           ; my multiplex ID?
	jne chain_int2d
    cmp al, 0                       ; Installation check? 
    jne int2d_end
    dec al                      ; set AL = FF
    mov cx, cs:TSR_Ver          ; CH = major; CL = minor
    mov dx, cs                  ; DX:DI points to sig string
    mov di, offset TSR_Sig
int2d_end:	
	iret

chain_int2d:
	db 0eah		; Jump Far
_OldInt2D  	dd 0


END_int2d_handler_:
	nop

I_ASMTEXT ENDS

END




