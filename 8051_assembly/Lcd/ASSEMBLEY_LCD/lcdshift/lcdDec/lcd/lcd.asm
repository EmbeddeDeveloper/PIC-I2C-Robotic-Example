;SW lcd.asm
;--------------------------------------------------------------------
;lcd_init	
;wr_lcd_cw0
;clear_display	
;wr_lcd_cw	
;wr_lcd_dw
;wr_lcd_data
;busy?	
;mov_lcd_cursor	
;clear_display
;toggle_e
;wr_lcd_hex	
;-------------------------------------------------------------------------
;-------------------------------------------------------------------------

lcd_init:
	call	wait_5ms
	call	wait_5ms
	call	wait_5ms
;
	mov	a,#30h	; port P07..P04 connected to d7_d4
	call	wr_lcd_cw0		
;-------------------------------------------------------------------------
	call	wait_5ms		;4.1ms
	mov	a,#30h			;
	call	wr_lcd_cw0
;-------------------------------------------------------------------------
	call	wait_5ms		;call	wait_100us
	mov	a,#30h			;
	call	wr_lcd_cw0
;----------------------------------------------------------------------
	call	wait_5ms		;call	wait_100us
	mov	a,#20h			;
	call	wr_lcd_cw0
;----------------------------------------------------------------------
lcd_init1:
		;function set init
		;rs=0, r/w=0, code= 0010 n f * * (8-bits)
		;n= 0 	1-line disp	f= 0  5x7 font
		; = 1 	2-line disp	 = 1  5x10 font
		;00101000b	;1-line, 5x7 font	;

;
	mov	a,#00101000b	;
	call	wr_lcd_cw
;-------------------------------------------------------------------------
		;cursor/disp shift(3rd command)	
		;rs=0, r/w=0, code= 0001 s/c r/l * *
		;s/c r/l= 00 cursor shifts left ie.-- add_counter
		;01 right ie.  ++ add_counter 		
		;10 display shifts left ie.cursor follows the display
		;11 right;00010100b	;cursor shifts right
;
;	mov	a,#00010100b	;
;	call	wr_lcd_cw
;-------------------------------------------------------------------------
		;disp on/off control(2nd command)
		;r/s=0, r/w=0, code= 0000 1 d c b
		;d= 0 disp off,c= 0 cursor off,b= 0 blink off
		;   1      on,	   1        on  ,   1       on
		;00001111b	;00001100b
		;disp,on,cursor & blink off.
;
;	mov	a,#00001110b	;
	mov	a,#08h		;display off cursor off
	call	wr_lcd_cw
	
	mov	a,#0ch		;display on cursor on
	call	wr_lcd_cw
;-------------------------------------------------------------------------
		;entry mode set
		;r/s=0, r/w=0, code= 000001 i/d s
		;i/d= 0 --add_counter, disp code & cursor shifts left	
		;   = 1 ++add_counter, right
		;s= 0 disable disp shift
		; = 1 shift disp right(i/d=0) or left(i/d=1)
		;0000 0110b;displays code & cursor shifts right & 		;++add_counter
;
;	mov	a,#00000110b	;
	mov	a,#05h		;cursor fixed &display shift enable
	call	wr_lcd_cw

	mov	a,#00001110b	;display cursor blinking
	call	wr_lcd_cw

	mov	a,#1ch		;display shift left
	call	wr_lcd_cw
;-------------------------------------------------------------------------
		;clear display
		;r/s=0, r/w=0, code= 0000 0001 
		;sets add_counter=0
		;space code= 20h in all ddram addresses
		;sets i/d=1
		;cursor at left end of display
		;00000001b
;
	mov	a,#00000001b	;
	call	wr_lcd_cw
;
;-------------------------------------------------------------------------
	clr	p0.0		;backlight on
;-------------------------------------------------------------------------
	ret
;-------------------------------------------------------------------------




;------------------------------------------------------
;write lcd control word. (control word in a) 
;without 5msec wait.
wr_lcd_cw0:
	call	map
	clr	rs		;Control 
	clr	r/w		;write
	call	toggle_e
	ret	
;------------------------------------------------------

;-----------------------------------------------------------
;clears display and moves cursor to start position.
clear_display:
	push	a
	call	busy	
	mov	a,#00000001b
	call	wr_lcd_cw
	call	wait_5ms
	pop	a
	ret
;------------------------------------------------------------


;------------------------------------------------------------
;set address in ddram		;address in a.(ie. 1xxxxxxxb)
;cursor moves to new address

mov_lcd_cursor:

;write lcd control word. (control word in a)

wr_lcd_cw:
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

;------------------------------------------------------
;write lcd data word. (data word in a)
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



;------------------------------------------------------
;converts 00..09 to display 0..9 (ascii) on lcd
wr_lcd_data:
	add	a,#30h
	call	wr_lcd_dw
	ret
;------------------------------------------------------



;------------------------------------------------------
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
;------------------------------------------------------
;writes the message starting at the first location
;after 16 positions..it corrects the address for proper
;2 line 16 charc display.
;the string should be terminated by 03h.

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





;-------------------------------------------------------------------------
;SW lcd.asm