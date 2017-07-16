;SW asm\isr_tab
;--------------------------------------------------------------------
	org     0003h
	reti			;ljmp	isr_i0
;
	org     000bh
	ljmp    isr_t0		;timer0 interrupt
;
	org     0013h
	reti			;ljmp    isr_i1
;
	org     001bh
	reti
				;ljmp isr_t1;timer1 interrupt
				;(isr_t1)baud rate for Usart
				;(...hence no Interrupt)
;
	org     0023h
         	reti
				;ljmp    isr_receive         
				;Interrupt enabled only for receive.
;
	org     002bh
         	reti
				;ljmp    isr_t2
;
;--------------------------------------------------------------------

;--------------------------------------------------------------------
;SW asm\isr_tab