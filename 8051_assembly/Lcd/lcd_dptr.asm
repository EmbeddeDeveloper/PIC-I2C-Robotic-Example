rs		bit		p0.1
rw		bit		p0.2
e		bit		p0.3
db4		bit		p0.4
db5		bit		p0.5
db6		bit		p0.6
db7		bit		p0.7

a4		bit		acc.4
a5		bit		acc.5
a6		bit		acc.6
a7		bit		acc.7
//....................................................................................
org		0fffh
data1:	db	"hello guys.",0
data2:	db	"whatz up?",0
//....................................................................................

org		0000h
		call	initial
		mov	dptr,#data1
again1:	        mov	a,#00h
		movc	a,@a+dptr
		jz	next  
		call	data_wrt
		inc	dptr
		jmp	again1

next:		mov	a,#0c0h
		call	cmd_wrt
		call	w8_5ms

		mov	dptr,#data2
next1:		mov	a,#00h
		movc	a,@a+dptr
		jz	stop
		call	data_wrt
		inc 	dptr
		jmp	next1
stop:		jmp	$
//.....................................................................................
//.....................................................................................
initial:
	call 	w8_15ms
	mov	a,#30h
	call	cmd_wrt1
	call	w8_5ms

	mov	a,#30h
	call	cmd_wrt1
	call	w8_5ms

	mov	a,#30h
	call	cmd_wrt1
	call	w8_5ms

	mov	a,#20h
	call	cmd_wrt1
	call	w8_5ms

//.....................................................................................
 	mov	a,#28h
	call	cmd_wrt
	call	w8_5ms

	mov	a,#0eh
	call	cmd_wrt
	call	w8_5ms

	mov	a,#01h
	call	cmd_wrt
	call	w8_5ms

	mov	a,#06h
	call	cmd_wrt
	call 	w8_5ms

	mov	a,#80h
	call	cmd_wrt
	call	w8_5ms

	clr	p0.0

	ret
//......................................................................................
//......................................................................................

cmd_wrt1:
	call	w8_5ms
	clr	rs
	clr	rw
	call	map
	call	enable
	ret

cmd_wrt:
	call	w8_5ms
	clr	rs
	clr	rw
	call	map
	call	enable
	swap	a
	call	map
	call	enable
	ret
//.....................................................................

data_wrt:
	call	w8_5ms
	setb	rs
	clr	rw
	call	map
	call	enable
	swap	a
	call	map
	call	enable
	ret
//......................................................................
enable:		
	setb	e
	nop
	clr	e
	ret
//.......................................................................

map:		
	mov	c,a4
	mov	db4,c
	
	mov	c,a5
	mov	db5,c
	
	mov	c,a6
	mov	db6,c
	
	mov	c,a7
	mov	db7,c
	ret
//.........................................................................
w8_5ms:	
	mov	r0,#09
d1:	mov	r1,#255
	djnz	r1,$
	djnz	r0,d1
	ret

w8_15ms:	
	mov	r2,#03
d2:	call	w8_5ms
	djnz	r2,d2
	ret
//.........................................................................
end