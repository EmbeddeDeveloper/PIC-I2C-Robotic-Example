;SW keys/key.asm
;--------------------------------------------------------------------
;keyprocess
;key_release
;get_key
;get_key_status
;--------------------------------------------------------------------
;-------------------------------------------------


keyprocess:
	mov	a,key_code
;
	cjne	a,#"A",chk_b

	call	process_a
	jmp	out_kp
;---------------------------
chk_b:	cjne	a,#"B",chk_c

	call	process_b
	jmp	out_kp
;---------------------------
chk_c:	cjne	a,#"C",chk_d

	call	process_c
	jmp	out_kp
;---------------------------
chk_d:	cjne	a,#"D",out_kp

	call	process_d
	jmp	out_kp
;-----------------------------
out_kp:
	call	key_release
	ret
;-------------------------------------------------
;---------------------------------------------------------------------
key_release:
	IF	HEX_KEYPAD
	jnb	nkp,$	;wait for no key press flag
	clr	key_ready
	clr	nkp
	ret
	ENDIF
;-------------------------------------------------
	IF	PC_KEYBOARD
	ret
	ENDIF
;-------------------------------------------------	
;---------------------------------------------------------------------
;gets ascii code for key pressed in "a" and key_code.
get_key:
	IF	HEX_KEYPAD
	jnb	key_ready,$
	mov	a,key_code
	mov	dptr,#ascii_key
	movc	a,@a+dptr
	mov	key_code,a
	ret
;------------------------------------------------------
ascii_key:	db	"0123456789ABCDEF"
	ENDIF
;-------------------------------------------------
	IF	PC_KEYBOARD
	call	rx
	mov	key_code,a
	ret
	ENDIF
;---------------------------------------------------------------------	
;---------------------------------------------------------------------
;gets ascii code for key pressed in "a" and key_code.
get_key_status:
	IF	HEX_KEYPAD	
	mov	c,key_ready
	ret
	ENDIF
;-------------------------------------------------
	IF	PC_KEYBOARD
	mov	c,ri
	ret
	ENDIF
;-------------------------------------------------
;---------------------------------------------------------------------




;--------------------------------------------------------------------
;SW keys/key.asm