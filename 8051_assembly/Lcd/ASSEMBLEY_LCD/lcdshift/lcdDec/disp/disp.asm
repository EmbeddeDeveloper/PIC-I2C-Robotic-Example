;SW sw/disp/disp.asm
;--------------------------------------------------------------------
;disp_sw
;disp_sw_started
;disp_sw_stopped
;disp_sw_resetted
;disp_count
;disp_sw_decremented
;--------------------------------------------------------------------
;--------------------------------------------------------------------


disp_sw:
	IF	SSD
	mov	ds1,#"Z"+1
	mov	ds2,#"Z"+1
	mov	ds3,#"W"
	mov	ds4,#"S"
	ret
	ENDIF
;----------------------------------------------
	IF	LCD
	call 	clear_display
	mov	dptr,#m_sw
	call	wr_lcd_message16
	ret
;		-1234567890123456-
m_sw:	db	" WELCOME TO THE "
	db	" STOP WATCH PROG",#03h
	ENDIF
;----------------------------------------------
	IF	TERMINAL
	mov	dptr,#m_sw
	call	send_m
	ret

m_sw:
;		-0        1         2         3         4	
;		-1234567890123456789012345678901234567890-
	db	"WELCOME TO THE STOPWATCH PROGRAM",#0Ah,#0Dh
	db	"Press A key to start the Stopwatch",#0Ah,#0Dh
	db	"Press B key to stop  the Stopwatch",#0Ah,#0Dh
	db	"Press C key to reset the Stopwatch",#0Ah,#0Dh,#03h
	ENDIF
;----------------------------------------------
;--------------------------------------------------------------------
;--------------------------------------------------------------------
disp_sw_started:
	IF	SSD
	ret
	ENDIF
;----------------------------------------------
	IF	LCD
	call 	clear_display
	mov	dptr,#m_swstrt
	call	wr_lcd_message16
	mov	a,ds4
	call	wr_lcd_dw
	mov	a,ds3
	call	wr_lcd_dw
	mov	a,ds2
	call	wr_lcd_dw
	mov	a,ds1
	call	wr_lcd_dw
;
	ret

m_swstrt:
;		-1234567890123456-
	db	"    STOPWATCH   "
	db	" STARTED ",#03h
	ENDIF
;----------------------------------------------
	IF	TERMINAL
	mov	a,#0Dh
	call	tx
	mov	dptr,#m_swstrt
	call	send_m
	ret

m_swstrt:
;		-0        1         2         3         4	
;		-1234567890123456789012345678901234567890-
	db	"STOPWATCH STARTED",#03h
	ENDIF
;----------------------------------------------
;--------------------------------------------------------------------

disp_sw_stopped:
	IF	SSD
	ret
	ENDIF
;----------------------------------------------
	IF	LCD
	call 	clear_display
	mov	dptr,#m_swstp
	call	wr_lcd_message16
	mov	a,ds4
	call	wr_lcd_dw
	mov	a,ds3
	call	wr_lcd_dw
	mov	a,ds2
	call	wr_lcd_dw
	mov	a,ds1
	call	wr_lcd_dw
;
	ret
;----------------------------------------------------------
m_swstp:
;		-1234567890123456-
	db	"    STOPWATCH   "
	db	" STOPPED ",#03h
	ENDIF
;----------------------------------------------
;----------------------------------------------
	IF	TERMINAL
	mov	a,#0Dh
	call	tx
	mov	dptr,#m_swstp
	call	send_m
	ret

m_swstp:
;		-0        1         2         3         4	
;		-1234567890123456789012345678901234567890-
	db	"STOPWATCH STOPPED-->  ",#03h
	ENDIF
;----------------------------------------------
;-------------------------------------------------------------------
;--------------------------------------------------------------------

disp_sw_resetted:
;----------------------------------------------
	IF	SSD
	ret
	ENDIF
;----------------------------------------------
;----------------------------------------------
	IF	LCD
	call 	clear_display
	mov	dptr,#m_swrst
	call	wr_lcd_message16
;
	mov	a,ds4
	call	wr_lcd_dw
;
;
	mov	a,ds3
	call	wr_lcd_dw
;
;
	mov	a,ds2
	call	wr_lcd_dw
;
;
	mov	a,ds1
	call	wr_lcd_dw
;
	ret

m_swrst:
;		-1234567890123456-
	db	"    STOPWATCH   "
	db	"RESETTED ",#03h
	ENDIF
;----------------------------------------------
;----------------------------------------------
	IF	TERMINAL
	mov	a,#0Dh
	call	tx
	mov	dptr,#m_swrst
	call	send_m
	ret

m_swrst:
;		-0        1         2         3         4	
;		-1234567890123456789012345678901234567890-
	db	"STOPWATCH RESETTED--> ",#03h
	ENDIF
;----------------------------------------------
;-------------------------------------------------------------------
disp_sw_decremented:
;----------------------------------------------
	IF	SSD
	ret
	ENDIF
;----------------------------------------------
	IF	LCD
	call 	clear_display
	mov	dptr,#m_swdec
	call	wr_lcd_message16
	mov	a,ds4
	call	wr_lcd_dw
	mov	a,ds3
	call	wr_lcd_dw
	mov	a,ds2
	call	wr_lcd_dw
	mov	a,ds1
	call	wr_lcd_dw
;
	ret

m_swdec:
;		-1234567890123456-
	db	" STOPWATCH      "
	db	" DOWN_C  ",#03h
	ENDIF
;----------------------------------------------
;----------------------------------------------
	IF	TERMINAL
	mov	a,#0Dh
	call	tx
	mov	dptr,#m_swstp
	call	send_m
	ret

m_swstp:
;		-0        1         2         3         4	
;		-1234567890123456789012345678901234567890-
	db	"STOPWATCH STOPPED-->  ",#03h
	ENDIF



;--------------------------------------------------------------------
disp_count:
;----------------------------------------------
	IF	SSD
	ret
	ENDIF
;----------------------------------------------
;----------------------------------------------
	IF	LCD
	mov	a,#c0h+9d
	call	mov_lcd_cursor
;
	mov	a,ds4
	call	wr_lcd_dw
;
;
	mov	a,ds3
	call	wr_lcd_dw
;
;
	mov	a,ds2
	call	wr_lcd_dw
;
;
	mov	a,ds1
	call	wr_lcd_dw
;
	call	wait_1sec
	ret
	ENDIF
;----------------------------------------------
;----------------------------------------------
	IF	TERMINAL	
;
	mov	a,ds4
	call	tx
;
	mov	a,ds3
	call	tx
;
	mov	a,ds2
	call	tx
;
	mov	a,ds1
	call	tx
;
;Escape sequence (VT100) for moving cursor back 4 positions..( ESC[4D )
	mov	a,#1bh		;ESC
	call	tx
;
	mov	a,#"["
	call	tx
;
	mov	a,#"4"
	call	tx
;
	mov	a,#"D"
	call	tx
;
	ret
	ENDIF
;----------------------------------------------
;-------------------------------------------------------------------






;------------------------------------------------------------------
;SW sw\disp\disp.asm