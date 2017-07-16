	d4:	REG	 p0.4
	d5:	REG	p0.5
	d6:	REG 	p0.6
	d7:	REG	p0.7
;-------------------------------
	rs:	REG 	p0.1
	rw:	REG 	p0.2
	e:	REG 	p0.3
;-------------------------------
	org 0000h
	mov tmod,#20h
	mov th1,#0fdh
	setb ren
	mov scon,#52h
	setb tr1
main:
	call init
l1:	mov r7,#16d
	;mov a,#80h
	;call cmd
	;call delay


	mov a,#28h
	call cmd
	call delay

l5:	mov a,#00h
	call rx 
	call tx
	mov a,sbuf
        call datar
	call delay

	djnz r7,l5
;--------------------------
	
	mov a,#0c0h
	call cmd
	call delay

	mov r7,#16d
	
l6:     mov a,#00h
	call rx 
	call tx
	mov a,sbuf
	call datar
	call delay

	djnz r7,l6


	mov a,#01h
	call cmd
	call delay
	jmp l1
;----------------------------

tx:
	jnb ti,$
	mov sbuf,a
	clr ti
	ret

rx:	jnb ri,$
	mov a,sbuf
	clr ri
	ret
;----------------------------
init:
	call delay
	call delay
	call delay
	call delay
	clr p0.0

	mov a,#00101000b
	call cmd
	call delay

	mov a,#00010100b
	call cmd
	call delay
	
	mov a,#00001100b
	call cmd
	call delay

	mov a,#00000110b
	call cmd
	call delay

	mov a,#00000001b
	call cmd
	call delay

	mov a,#02h
	call cmd
	call delay
	ret
;-------------------------------

cmd:
	call busy
	push acc
	clr rs
	clr rw
	call map
	call enable
	pop acc
	swap a
	call map
	call enable
	ret
;---------------------------------
enable:
	setb e
	nop
	nop
	nop
	nop
	clr e
	ret
;-------------------------------

busy:
	setb d7
	clr rs
	setb rw
	setb e
	nop
	mov c,d7
	nop
	clr e
	jc busy
	ret
;---------------------------------------
map:
	mov c,acc.4
	mov d4,c
	mov c,acc.5
	mov d5,c
	mov c,acc.6
	mov d6,c
	mov c,acc.7
	mov d7,c
	ret
;---------------------------------------
datar:	call busy
	setb rs
	clr rw
	push acc
	call map
	call enable
	pop acc
	swap a
	call map
	call enable
	ret
;---------------------------------------
delay:
	mov r1,#100d
  g1:	mov r2,#23d
	djnz r2,$
	djnz r1,g1
	ret
;-------------------------------
delay1:
	mov r1,#5d
  g7:	mov r2,#255d
  g8:	mov r3,#255d
	djnz r3,$
	djnz r2,g8
	djnz r1,g7
	ret
;-------------------------------
	END
	