;SW sw.asm
;--------------------------------------------------------------------
	CHIP 8052
	.list on
;--------------------------------------------------------------------
;conditional assembly...
;Choice of outputs..
SSD:		EQU	0
LCD:		EQU	1
TERMINAL:	EQU	0
;choice of inputs..
HEX_KEYPAD	EQU	1
PC_KEYBOARD	EQU	0
;--------------------------------------------------------------------
	include	c:\lcdDec\data\reg.asm
	include	c:\lcdDec\data\equ.asm
;--------------------------------------------------------------------
	org 	0000h
	jmp	main
;--------------------------------------------------------------------
	include	c:\lcdDec\asm\isr_tab.asm
;--------------------------------------------------------------------
;Specification for stopwatch...
;A --> START	;start the stopwatch from the current count.
;B --> STOP	;stops the stopwatch current count frozen.
;C --> RESET	;reset the stopwatch to 0000.
;--------------------------------------------------------------------
main:
	 clr 	stop_sw
      	mov	sp,#top_of_stack
	setb	ea		;enable all interrupts.
	call	init	;init timer,test's display,etc.
;
	call	disp_sw	;display stopwatch
l1_main:
	call	get_key_status	;carry set indicated key 				;pressed
	jc	l2_main
	jb	first_time,l1_main
	call	disp_count
	jmp	l1_main
l2_main:
	call	get_key
	call	keyprocess
	jmp	l1_main

;--------------------------------------------------------------------
	include	c:\lcdDec\asm\init.asm
	include	c:\lcdDec\asm\isr.asm
	include	c:\lcdDec\util\delay.asm
	include	c:\lcdDec\util\test.asm
	include	c:\lcdDec\keys\appl_kp.asm
	include	c:\lcdDec\keys\appl.asm
;
	include	c:\lcdDec\keys\key.asm
	include	c:\lcdDec\disp\disp.asm
;
	IF	LCD
	include	c:\lcdDec\lcd\lcd.asm
	ENDIF
;
	IF	TERMINAL
	include	c:\lcdDec\uart\uart.asm
	ELSE
		
	IF	PC_KEYBOARD
	include	c:\lcdDec\uart\uart.asm
	ENDIF	
           

         ENDIF
;
;--------------------------------------------------------------------
	end
;--------------------------------------------------------------------
;SW sw.asm	