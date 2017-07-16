org 0000h
	 
	mov p0,#00h
	mov tmod,11011101b
	mov a,#0h
	mov r0,#0h
	setb t0
	setb t1
	setb tr0
	setb tr1
main:
l2:	jb t0,l1
	inc a
	mov p0,a
l1:	jb t1,l2
	dec r0
	mov a,r0
	mov p0,a
	jmp main
end

