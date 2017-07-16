
ds1 equ 30h
ds2 equ 31h
ds3 equ 32h
ds4 equ 33h 

dcount_1 equ 34h
dcount_2 equ 35h
dcount_3 equ 36h

sl1 bit p2.0
sl2 bit p2.1
sl3 bit p2.2
sl4 bit p2.3

org 0000h

loop:
	clr sl1
	setb sl2
	setb sl3
	setb sl4
	mov ds1,#01100000b
	mov p0,ds1
	call delay
	
	setb sl1
	clr sl2
	setb sl3
	setb sl4
	mov ds2,#11011010b
	mov p0,ds2
	call delay
	
	setb sl1
	setb sl2
	clr sl3
	setb sl4
	mov ds3,#11110010b
	mov p0,ds3
	call delay
	
	setb sl1
	setb sl2
	setb sl3
	clr sl4
	mov ds4,#01100110b
	mov p0,ds4
	call delay
	jmp loop
 	
delay:
	mov dcount_3,#07h
l2:	mov dcount_2,#50h
l1:	mov dcount_1,#0ffh
	djnz dcount_1,$
	djnz dcount_2,l1
	djnz dcount_3,l2
	ret
	end