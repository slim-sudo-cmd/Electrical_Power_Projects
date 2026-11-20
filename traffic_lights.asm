
; >>> Follow on Github -> https://github.com/slim-sudo-cmd
; >> Electrical projects   
.MODEL SMALL
.STACK 100h

port_addr EQU 04h

.DATA
State_Table DB 00100001b, 1  ; Main RED,   Side AMBER (1 unit)
            DB 01000001b, 2  ; Main RED,   Side GREEN (2 units)
            DB 00100010b, 1  ; Main AMBER, Side AMBER (1 unit)
            DB 00010100b, 4  ; Main GREEN, Side RED   (4 units)
            DB 00010010b, 1  ; Main AMBER, Side RED   (1 unit)

Number_State EQU 5

.CODE
main proc
    mov ax,@DATA
    mov ds,ax

CYCLE_LOOP:
    mov si,OFFSET State_Table
    mov cx,Number_State

NEXT_STATE:
    mov al,[si]    
    out Port_addr,al
    inc si

    mov bl,[si] 
    inc si

    push cx
    mov bh,0
    mov cx,bx

UNIT_LOOP:
    call Delay_One_Unit
    loop UNIT_LOOP

    pop cx
    loop NEXT_STATE

    jmp CYCLE_LOOP
    
MAIN ENDP

Delay_One_Unit PROC
    push ax
    push bx
    push cx
    push dx

    mov dx,0098h

OUTER_DELAY:
    mov cx,0FFFFh

INNER_DELAY:
    nop
    loop INNER_DELAY
    dec dx
    jnz OUTER_DELAY

    pop dx
    pop cx
    pop bx
    pop ax
    ret

Delay_One_Unit ENDP

END MAIN


