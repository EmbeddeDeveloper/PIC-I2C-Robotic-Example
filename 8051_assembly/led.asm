org 0000h
;---------------initialization part--------------
count1	equ	30h
count2	equ	31h
count3	equ	32h
;------------------------------------------------
main:	
	mov p0,#0f0h
        call delay 
        mov p0,#0fh
        call delay
        jmp main
;-----------delay for 1sec-------------------------
delay:
    mov  count1,#07h
L1:
    mov  count2,#0ffh
L2:
    mov  count3,#0ffh
    djnz count3,$
    djnz count2,L2
    djnz count1,L1

    ret
;--------------------------------------------------
   end