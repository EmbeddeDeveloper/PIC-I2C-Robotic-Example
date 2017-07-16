;SW keys/appl.asm
;--------------------------------------------------------------------
;inc_d
;dec_d
;----------------------------------------------------------
;-----------------------------------------------
inc_d:  	jnb     	start_sw,out1_id
	inc 	ds1
	mov 	a,ds1
	cjne 	a,#"9"+1,$+3
	jnc 	l1_id 
	ret
;
l1_id:	mov 	ds1,#"0"
	inc 	ds2
	mov 	a,ds2
	cjne 	a,#"9"+1,$+3
	jnc 	l2_id
	ret
;
l2_id:	mov 	ds2,#"0"
	inc 	ds3
	mov 	a,ds3
	cjne 	a,#"9"+1,$+3 
	jnc 	l3_id
	ret
;
l3_id:	mov 	ds3,#"0"
	inc 	ds4 
	mov 	a,ds4
	cjne 	a,#"9"+1,out1_id
        	jnc 	l4_id
       	 ret
;  

l4_id:	mov	ds1,#"0"
	mov	ds2,#"0"
	mov	ds3,#"0"
	mov	ds4,#"0"
        	ret
;

out1_id:
	ret
;-------------------------------------------------
dec_d: 	jnb	stop_sw,out2_id 
	dec 	ds1
	mov 	a,ds1
	cjne 	a,#"0",$+3
	jc 	l5_id 
	ret
;
l5_id:	mov 	ds1,#"9"
	dec 	ds2
	mov 	a,ds2
	cjne 	a,#"0",$+3
	jc 	l6_id
	ret
;
l6_id:	mov 	ds2,#"9"
	dec 	ds3
	mov 	a,ds3
	cjne 	a,#"0",$+3 
	jc 	l7_id
	ret
;
l7_id:	mov 	ds3,#"9"
	dec	ds4 
	mov 	a,ds4
	cjne 	a,#"0",$+3
        	jnc 	out2_id
       	 
;  
	mov	ds1,#"9"
	mov	ds2,#"9"
	mov	ds3,#"9"
	mov	ds4,#"9"
       	
;
out2_id:
	ret
;-------------------------------------------------



;--------------------------------------------------------------------
;SW keys/appl.asm
