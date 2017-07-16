;SW data\data.def 
;-------------------------------------------------------------------
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
rs:   	REG     P0.1    ;resgister select for LCD
r/w:   	REG     P0.2	;read/write for LCD
e:   	REG     P0.3	;enable for LCD
d4:   	REG     P0.4	;data bit d4 for LCD
d5:  	REG     P0.5	;data bit d5 for LCD
d6:   	REG     P0.6	;data bit d6 for LCD
d7:  	REG     P0.7	;data bit d7 for LCD
;
sl1:	REG	P2.0		;display1/row1
sl2:	REG	P2.1		;display2/row2
sl3:	REG	P2.2		;display3/row3
sl4:	REG	P2.3		;display4/row4
;
krl1:	REG	p2.4		;key return line 1
krl2:	REG	p2.5		;key return line 2
krl3:	REG	p2.6		;key return line 3
krl4:	REG	p2.7		;key return line 4

;----------------------------------------------------
key_ready:	REG	00h	;this flag is set when key is detected (after debounce).
nkp:		REG	01h	;this flag is set when no key is pressed.
tb:		REG	02h	;temp bit location
;----------------------------------------------------
start_sw:	REG	03h	;
s1_over:	REG	04h	;
first_time:	REG	05h	;
start_buzzer:	REG	06h	;buzzer bit
dow:            REG     07h
stop_sw:		reg	08h            ;decriment flag
;--------------------------------------------------------------------

;-------------------------------------------------------------------
;SW data\data.def 