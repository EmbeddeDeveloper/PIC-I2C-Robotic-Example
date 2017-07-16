;SW asm\init.asm
;--------------------------------------------------------------------
;init
;init_timer0
;init_timer1
;init_uart
;init_keypad
;init_delay_1sec
;init_sw
;----------------------------------------------------------

init:
;--------------------------
	call	init_timer0	;for 1ms interrupt
;--------------------------
	IF	SSD
	call	test_display	;in disp\disp.asm 
	ENDIF
;---------------------------
	IF	LCD
	call	lcd_init		;in lcd\lcd.asm
	ENDIF
;--------------------------
	IF	TERMINAL
	call	init_timer1	;for baud rate (9600)
	call	init_uart
	setb	ti
	ELSE
		
	IF	PC_KEYBOARD
		call	init_timer1     ;for baud rate (9600)
		call	init_uart
		setb	ti
		ENDIF
	ENDIF
;------------------------------------------------
	call	init_keypad
;-------------------------------------------------
	call	init_delay_1sec
;-------------------------------------------------
	call	init_sw
;--------------------------------------------------
	ret
;----------------------------------------------------------
;----------------------------------------------------------
;(89h)
;TMOD-->GATE, C/T, M1,M0, GATE, C/T, M1, M0,T/C	(timer1,timer0)
;init timer 0  for 1msec

init_timer0:
	orl	tmod,#01h	       ;t0 in 16 bit timer mode.
	mov	tl0,#66h	;Init timer0 with countfor 1msec.
	mov	th0,#0fch	;count=0fc66h for 1msec.
	setb	tr0	;start timer 0.
        	setb	et0	;enable timer 0 Interrupt.
	ret 
;----------------------------------------------------------
;----------------------------------------------------------
init_timer1:
	orl	tmod,#20h  ;t1 in 8 bit auto reload mode.
	mov     	th1,#0fdh    ;init. TH1 with count for
			  ;9600 baud (11.059MHz)
	setb	tr1               ;Start timer 1 (baud rate)
	ret 
;----------------------------------------------------------
;----------------------------------------------------------
;Code to initialise serial port.
init_uart:
	mov     scon,#01000000b        ;Init. serial control ie 			             		             ;mode 1 ( 8 bit uart);8 bit 			            			             ;UART mode(variable).
	clr	ri                            ;Clear Receive Interrupt
	clr	ti                             ;Clear Transmit Interrupt
	setb	ren                         ;enable receiver
	setb   	es                  ;Enable serial interrupt
	ret
;----------------------------------------------------------
;----------------------------------------------------------
init_keypad:
	setb	krl1
	setb	krl2
	setb	krl3
	setb	krl4
	mov	scan_no,#00d
	mov	dcount,#33d
	mov	krcount,#32d
	
	clr	key_ready
	clr	nkp
	clr	start_buzzer
	ret
;--------------------------------------------------------------------
;--------------------------------------------------------------------
init_delay_1sec:
	mov	cnt_1sl,#0e8h
	mov	cnt_1sh,#04h
	setb	s1_over
	ret
;--------------------------------------------------------------------
;--------------------------------------------------------------------
init_sw:
	clr	start_sw
	clr	stop_sw
	setb	first_time
	ret
;--------------------------------------------------------------------




;--------------------------------------------------------------------
;SW asm\init.asm