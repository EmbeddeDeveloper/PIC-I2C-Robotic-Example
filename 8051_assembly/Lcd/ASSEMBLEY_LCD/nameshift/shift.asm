;nameshift	.asm	
;define bit variables here...
;
a0:	REG	A.0
a1:	REG	A.1
a2:	REG	A.2
a3:	REG	A.3
a4:	REG	A.4
a5:	REG	A.5
a6:	REG	A.6
a7:	REG	A.7
;
rs:   	REG     P0.1   	 ;resgister select for LCD
r/w:   	REG     P0.2	;read/write for LCD
e:   	REG     P0.3	;enable for LCD
d4:   	REG     P0.4	;data bit d4 for LCD
d5:  	REG     P0.5	;data bit d5 for LCD
d6:   	REG     P0.6	;data bit d6 for LCD
d7:  	REG     P0.7	;data bit d7 for LCD

count16:	equ	30h
dcount_1:	equ	31h
dcount_2:	equ	32h
dcount_3:	equ	33h
;--------------------------------------------------------------------------
	org 	0000h
	call	init_lcd
	call	clear_display
main:	mov	dptr,#s_wr
	call	lcd_msg16
	mov	a,#80h
	call	lcd_wc
	call	wait_1sec
	
	jmp	main

s_wr:	
;		-1234567890123456-
	db	"     PROLIFIC   "
	db	"****************",#03h


init_lcd:	call	wait_5ms
	call	wait_5ms
	call	wait_5ms
	mov	a,#30h
	call	lcd_wc0

	call	wait_5ms
	mov	a,#30h
	call	lcd_wc0
	
	call	wait_5ms
	mov	a,#30h
	call	lcd_wc0
	
	call	wait_5ms
	mov	a,#20h
	call	lcd_wc0
	
lcd_init1:	
	mov	a,#28h		;lcd type initialisation
	call	lcd_wc
	
	mov	a,#08h		;display off cursor off
	call	lcd_wc
	
	mov	a,#0ch		;display on cursor on
	call	lcd_wc
		
	mov	a,#05h	;cursor fixed and display shift enable
	call	lcd_wc
		
	mov	a,#0eh		;display cursor blinking
	call	lcd_wc
	
	mov	a,#18h		;display shift left
	call	lcd_wc
		
	mov	a,#01h		;clear display
	call	lcd_wc
	
	  
	clr	p0.0
	ret

;----------------------------------------------------------------------
mov_lcd_cursor:
lcd_wc:	
	push	a
	call	busy
	call	map
	clr	rs
	clr	r/w
	call	toggle_e
	
	swap	a
	call	map

	call	toggle_e
	
	pop	a
	ret
;-------------------------------------------------------------------

lcd_wd0:
	push	a
	call	busy
	call	map
	setb	rs
	clr	r/w
	call	toggle_e

	swap	a
	call	map
	call	toggle_e
	
	pop	a
	ret
;-------------------------------------------------------------
lcd_wc0:	
	
	call	map
	clr	rs
	clr	r/w
	call	toggle_e
		
	ret

;------------------------------------------------------------
clear_display:
	push	a
	call	busy
	mov	a,#01h
	call	lcd_wc
	pop	a
	ret
;-------------------------------------------------------------
map:	
	mov	c,a4
	mov	d4,c

	mov	c,a5
	mov	d5,c

	mov	c,a6
	mov	d6,c

	mov	c,a7
	mov	d7,c
	ret
;-----------------------------------------------------------------
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
;-------------------------------------------------------------------
busy:
	setb	d7
	clr	rs
	setb	r/w
	nop
	setb	e
	nop
	mov	c,d7
	clr	e

	nop
	call	toggle_e
	jc	busy
	ret
;----------------------------------------------------------------------
lcd_msg16:
	mov	count16,#00h
	push	a
	
wr_l1:	mov	a,#00h
	movc	a,@a+dptr
	cjne	a,#03h,wr_l2
	jmp	out_wr
wr_l2:
	call	lcd_wd0
	inc	dptr
	
	inc	count16
	mov	a,count16
	cjne	a,#16d,wr_l1
	mov	a,#0a8h
	
	call	mov_lcd_cursor
	jmp	wr_l1
;----------------------------------------------------
wait_5ms:
	mov	r2,#21d
l1:	mov	r3,#0ffh
	djnz	r3,$
	djnz	r2,l1
	ret
out_wr:
	pop	a
	ret
wait_1sec:
	
	mov	dcount_3,#07d
l2:	mov 	dcount_2,#0ffh
l3:	mov 	dcount_1,#0ffh
	djnz 	dcount_1,$
	djnz 	dcount_2,l3
	djnz 	dcount_3,l2
	ret
end