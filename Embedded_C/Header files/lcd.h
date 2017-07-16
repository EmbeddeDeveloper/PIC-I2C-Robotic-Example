/*--------------------------------------------------------------------------
LCD.H

Header file for generic 80C51 and 80C31 microcontroller.
Copyright (c) 1988-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __LCD_H__
#define __LCD_H__

/*COMMAND WRITE...*/
void cw()
{
	//busy();
	rs=rw=0;
	map();
	toggle();
	B=B<<4;
	map();
	toggle();
}

/* FOR DATA WRITE...*/
void dw1()
{
	//busy();
	rs=1;
	rw=0;
	map();
	toggle();
	B=B<<4;
	map();
	toggle();
}

/*CLOCK PULSE FOR SENDING DATA*/
void toggle()
{
	e=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	e=0;
	_nop_();
	_nop_();
	_nop_();
}

/*BUSY FUNCTON*/
void busy()
{
	d7=rw=e=1;
	rs=0;
	_nop_();
	_nop_();
	c=d7;
	_nop_();
	_nop_();
	e=0;
	toggle();
	if(c==1)
	{
		busy();
	}
}

/*SWAPING DATA...FORM 4BIT TO 8BIT*/
void map()
{
	d4=a4;
	d5=a5;
	d6=a6;
	d7=a7;
}					

#endif
