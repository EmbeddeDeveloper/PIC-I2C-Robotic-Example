
org 0000h

main:
	call uart
	mov a,#"A"
	call TX

	jmp main

uart:
	mov tmod,#20h
	mov th1,#0fdh
	mov scon,#50h
	setb TR1
	ret

TX:
	mov sbuf,a
	jnb TI,$
	clr TI
	ret

RX:
	jnb RI,$
	mov a,sbuf
	clr RI
	ret

end