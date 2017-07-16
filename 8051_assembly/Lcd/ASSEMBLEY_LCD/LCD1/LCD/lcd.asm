	a0:	reg	a.0
	a1:	reg	a.1
	a2:	reg	a.2
	a3:	reg	a.3
	a4:	reg	a.4
	a5:	reg	a.5
	a6:	reg	a.6
	a7:	reg	a.7

	rs:	reg	p0.1
	r/w:	reg	p0.2
	e:	reg	p0.3
	d4:	reg	p0.4
	d5:	reg	p0.5
	d6:	reg	p0.6
	d7:	reg	p0.7

	dcount_1:	equ	30h
	dcount_2:	equ	31h
	count16:	equ	32h
;----------------------------------

	org	0000h
	
	call	lcd_init
	call	clear_display
	mov	dptr,#m_sw
	call	wr_lcd_msg16
	ret

lcd_init:
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
	
	
;---------------------------------------------
lcd_init1:
				;set interface length
	mov	a,#00101000b	;001 DL N F * *
	call	lcd_cw		;call command write subrutine

				;mov cursor shift display
	mov	a,#00010100b	;0001 sc rl * *
	call	lcd_cw

				;enable display curser
	mov	a,#00001110b	;00001 d c b
	call	lcd_cw
			
				;entry mode set
	mov	a,#00000110b	;000001 i/d s
	call	lcd_cw

				;clear display
	mov	a,#00000001b	;00000001
	call	lcd_cw

	clr	p0.0
	ret
;----------------------------------------------	
;cursor move to new address
mov_lcd_cursor:

lcd_cw:
	
	push	a
	call	busy
	
	call	map
	
	clr	rs		;control
	clr	r/w		;write
	call	toggle_e

	swap	a
	call	map

	call	toggle_e

	pop	a
	ret
;----------------------------------------------
lcd_cw0:
	call	map
	clr	rs		;control
	clr	r/w		;write
	call	toggle_e
	ret
;----------------------------------------------
lcd_dw:
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
;----------------------------------------------
clear_display:
	push	a
	call	busy
	mov	a,#00000001b
	call	lcd_cw
	pop	a
	ret
;----------------------------------------------
busy:	
	setb	d7		;configure busy flag
	clr	rs		;status(conmmand)
	setb	r/w		;read
	nop
	setb	e
	nop
	mov	c,d7
	nop
	clr	e

	nop
	call	toggle_e
	jc	busy
	ret
;-----------------------------------------------
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
;-----------------------------------------------
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
;-----------------------------------------------
wait_5ms:
	mov	dcount_2,#21d
	mov	dcount_1,#0ffh		;$-3-3
	djnz	dcount_1,$		;$-3
	djnz	dcount_2,$-3-3
	ret
;------------------------------------------------
wr_lcd_msg16:
	mov	count16,#00h
	push	a
	
wr_l1:	mov	a,#00h
	movc	a,@a+dptr
	cjne	a,#03h,wr_l2
	jmp	out_wr

wr_l2:	
	call	lcd_dw
	inc	dptr

	inc	count16
	mov	a,count16
	cjne	a,#16d,wr_l1

	mov	a,#10101000b		;init new cursor position 10101001b
	call	mov_lcd_cursor

	jmp	wr_l1
out_wr:
	pop	a
	ret
;-----------------------------------------------

	
m_sw:
;		-1234567890123456-
	db	" PROLIFIC       "
	db	"****************",#03h

	