org 	0000h

mov	p0,#00h
mov	a,#00h
mov	r2,#00h
mov	tmod,#11011101b
setb	t0
setb	t1
setb	tr0
setb	tr1

again:
	jb 	t0,l1
	inc	r2
l1:	jb	t1,l2
	dec	r2
l2:	mov	a,r2
	mov	p0,a
	sjmp	again
	
end