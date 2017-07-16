;SW appl_kp.asm
;--------------------------------------------------------------------
;process_a
;process_b
;process_c
;process_d
;--------------------------------------------------------------------
;-------------------------------------------------

process_a:
	jnb	first_time,l1_pa
	clr	first_time
	mov	ds1,#"0"
	mov	ds2,#"0"
	mov	ds3,#"0"
	mov	ds4,#"0"
l1_pa:
	setb	start_sw
	clr	stop_sw
	call	disp_sw_started
	ret
;-------------------------------------------------
;-------------------------------------------------
process_b:
	clr	start_sw
	clr	stop_sw
	call	disp_sw_stopped
	ret
;-------------------------------------------------
;-------------------------------------------------
process_c:
	clr	start_sw
	clr	stop_sw

	mov	ds1,#"0"		;reset count to 0000
	mov	ds2,#"0"
	mov	ds3,#"0"
	mov	ds4,#"0"
;
	call	disp_sw_resetted
	ret
;-------------------------------------------------
process_d:
	
       	setb   	stop_sw
	clr	start_sw
	call    	disp_sw_decremented
	ret



;--------------------------------------------------------------------
;SW appl_kp.asm