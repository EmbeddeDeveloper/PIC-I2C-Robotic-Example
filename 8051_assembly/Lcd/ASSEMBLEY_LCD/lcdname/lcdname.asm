a0:	reg	A.0
a1:	reg	A.1
a2:	reg	A.2
a3:	reg	A.3
a4:	reg	A.4
a5:	reg	A.5
a6:	reg	A.6
a7:	reg	A.7

rs:	reg	P0.1
rw:	reg	P0.2
e:	reg	P0.3
d4:	reg	P0.4
d5:	reg	P0.5
d6:	reg	P0.6
d7:	reg	P0.7
	
dcount_1:	equ	30h
dcount_2:	equ	31h
dcount_3:	equ	32h
count16:		equ	33h
;----------------------------------------
	org	0000h
	call	init
	jmp	$


init:	
	call	init_lcd1
	call	clear_display
	mov	dptr,#m_sw
	call	wr_lcd_msg16
	ret
m_sw:
;		"-1234567890123456-"
	db	 "       prerna   " 
	db	 "****************",#03h
     	


wr_lcd_msg16:
	mov	count16,#00
	push	a
wr_l1:	mov	a,#00h
	movc	a,@a+dptr
	cjne	a,#03h,wr_l2
	jmp	out_wr

wr_l2:	call	lcd_dw
	inc	dptr

	inc	count16
	mov	a,count16
	cjne	a,#16d,wr_l1

	mov	a,#10101000b
	call	mov_lcd_cursor
	jmp	wr_l1

out_wr:
	pop	a
	ret
;----------------------------------
clear_display:
	push	a
	call	busy
	mov	a,#00000001b
	call	lcd_cw
	call	wait_5ms
	pop	a
	ret
init_lcd1:
	call	wait_5ms
	call	wait_5ms
	call	wait_5ms

	mov	a,#30h
	call	lcd_cw0

	call	wait_5ms
	mov	a,#30h
	call	lcd_cw0

	call	wait_5ms
	mov	a,#30h
	call	lcd_cw0

	call	wait_5ms
	mov	a,#20h
	call	lcd_cw0


init_lcd:
	mov	a,#00101000b		
	call	lcd_cw

	mov	a,#00010100b		;incriment curser & shift display
	call	lcd_cw

	mov	a,#00001110b	
	call	lcd_cw

	mov	a,#00000110b		;mov curser & shift display
	call	lcd_cw

	mov	a,#00000001b		;set interface length
	call	lcd_cw
	clr	P0.0
	ret

mov_lcd_cursor:
lcd_cw:	
	push	a
	call	busy
	call	map	
    	clr	rs
	clr	rw
	
	call	toggle_e

	swap	a

	call	map
	call	toggle_e
	pop	a
	ret
lcd_cw0:
	call	map
	clr	rs
	clr	rw
	call	toggle_e
	ret
lcd_dw:
	push	a
	call	busy	
	call	map
    	setb	rs
	clr	rw

	call	toggle_e

	swap	a

	call	map
	call	toggle_e
	pop	a
	ret
map:	
	mov	C,a4
	mov	d4,C

	mov	C,a5
	mov	d5,C

	mov	C,a6
	mov	d6,C

	mov	C,a7
	mov	d7,C

	ret
toggle_e:
	nop
	setb	e
	nop
	nop
	nop
	nop
	clr	e
	nop
	ret
;-------------------------------------
busy:
	setb	d7
	clr	rs
	setb	rw
	nop
	setb	e
	nop
	mov	c,d7
	nop
	clr	e
	ret
wait_5ms:
	mov	dcount_1,#2
l2:	mov	dcount_2,#100
l1:	mov	dcount_3,#250
	djnz	dcount_3,$
	djnz	dcount_2,l1
	djnz	dcount_3,l2
	ret
end