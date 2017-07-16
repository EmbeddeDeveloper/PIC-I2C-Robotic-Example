;define bit variables here...
;
A0:	REG	A.0
A1:	REG	A.1
A2:	REG	A.2
A3:	REG	A.3
A4:	REG	A.4
A5:	REG	A.5
A6:	REG	A.6
A7:	REG	A.7
;
rs:   	REG     P0.1   	 ;resgister select for LCD
r/w:   	REG     P0.2	;read/write for LCD
e:   	REG     P0.3	;enable for LCD
d4:   	REG     P0.4	;data bit d4 for LCD
d5:  	REG     P0.5	;data bit d5 for LCD
d6:   	REG     P0.6	;data bit d6 for LCD
d7:  	REG     P0.7	;data bit d7 for LCD

count16:	equ	30h
;-------------------------------------------------------------------------
	call	lcd_init
	call	clear_display
	mov	dptr,#m_sw
	call	wr_lcd_message16
	call	wait_1sec
	mov	a,#80
	ret
m_sw:	
	db	"   prolific     "
	db	"----------------",#03h 

lcd_init:
	call	wait_5ms
	call	wait_5ms
	call	wait_5ms
;
	mov	a,#30h		; port P07..P04 connected to d7_d4
	call	lcd_cw0		
;-------------------------------------------------------------------------
	call	wait_5ms		;4.1ms
	mov	a,#30h			;
	call	lcd_cw0
;-------------------------------------------------------------------------
	call	wait_5ms		;call	wait_100us
	mov	a,#30h			;
	call	lcd_cw0
;----------------------------------------------------------------------
	call	wait_5ms		;call	wait_100us
	mov	a,#20h			;
	call	lcd_cw0
;----------------------------------------------------------------------
lcd_init1:	
	mov	a,#28h		;lcd type initialisation
	call	lcd_cw
	
	mov	a,#08h		;display off cursor off
	call	lcd_cw
	
	mov	a,#0ch		;display on cursor on
	call	lcd_cw
		
	mov	a,#05h	;cursor fixed and display shift enable
	call	lcd_cw
		
	mov	a,#0eh		;display cursor blinking
	call	lcd_cw
	
	mov	a,#18h		;display shift left
	call	lcd_cw
		
	mov	a,#01h		;clear display
	call	lcd_cw
	
	  
	clr	p0.0
	ret
;------------------------------------------------------
lcd_cw0:
	call	map
	clr	rs		;Control 
	clr	r/w		;write
	call	toggle_e
	ret	
;------------------------------------------------------
clear_display:
	push	a
	call	busy	
	mov	a,#00000001b
	call	lcd_cw
	call	wait_5ms
	pop	a
	ret
;------------------------------------------------------------
mov_lcd_cursor:

lcd_cw:
	push	a
	call	busy		
;--------------------------------
	call	map
;--------------------------------
	clr	rs		;Control 
	clr	r/w		;write
	call	toggle_e
;--------------------------
	swap	a
	call	map
;--------------------------------
;
	call	toggle_e
;-------------------------------
	pop	a
	ret	
;------------------------------------------------------

wr_lcd_dw:
;--------------------------------
	push	a
	call	busy				
;--------------------------------
	call	map
;--------------------------------
	setb	rs		;data
	clr	r/w		;write
	call	toggle_e
;--------------------------------
	swap	a
	call	map
;--------------------------------
	call	toggle_e
;--------------------------------
	pop	a
	ret	
;------------------------------------------------------
;-----------------------------------------------------
busy:
;read lcd status word.
;
	 setb	d7		;config (busy flag) as i/p
	clr	rs		;Status(Control) 
	setb	r/w		;read
	nop
	setb	e
	nop
	mov	c,d7		;copy busy flag to carry.
	nop
	clr	e
;-------------------------------------------------------
	nop
	call	toggle_e
	jc	busy
	ret	
;------------------------------------------------------

;------------------------------------------------------
toggle_e:
	nop
	setb	e
	nop
	nop
	nop
	nop
	clr	e
	nop
;	
	ret
;------------------------------------------------------


;------------------------------------------------------
;maps value in a to lcd port.
map:
	mov	c,A4
	mov	d4,c
;
	mov	c,A5	
	mov	d5,c
;
	mov	c,A6	
	mov	d6,c
;
	mov	c,A7
	mov	d7,c
;
	ret	
;------------------------------------------------------
wr_lcd_message16:
	mov	count16,#00h
	push	a
wlm_l1:
	mov	a,#00h
	movc	a,@a+dptr
	cjne	a,#03h,wlm_l2
	jmp	out_wlm
wlm_l2:
	call	wr_lcd_dw	;write at the current cursor position.
	inc	dptr
;
	inc	count16		;init to 00h
	mov	a,count16
	cjne	a,#16d,wlm_l1
;
	mov	a,#10101000b	;init new cursor position. 10101001b
	call	mov_lcd_cursor	
;
	jmp	wlm_l1
;
out_wlm:
	pop	a
	ret

;------------------------------------------------------
wait_5ms:
	mov	r2,#21d
l1:	mov	r3,#0ffh
	djnz	r3,$
	djnz	r2,l1
	ret

end


;-------------------------------------------------------------------------
;SW lcd.asm