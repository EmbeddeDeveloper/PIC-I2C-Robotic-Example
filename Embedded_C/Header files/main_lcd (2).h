/*--------------------------------------------------------------------------
LCD.H

Header file for generic 80C51 and 80C31 microcontroller.
Copyright (c) 1988-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

#ifndef __MAIN_LCD_H__
#define __MAIN_LCD_H__
//-----------------------------------------
//-----------------------------------------
sbit back =P0^0;
sbit rs   =P0^1;
sbit rw   =P0^2;
sbit e	  =P0^3;
sbit d4	  =P0^4;
sbit d5	  =P0^5;
sbit d6	  =P0^6;
sbit d7	  =P0^7;

bit c;
extern void		_nop_     (void);
void 	init_lcd();
void 	wr_lcd_cw0(unsigned char);
void 	wr_lcd_cw(unsigned char);
void 	wr_lcd_dw(unsigned char);
void 	delay(unsigned int);
void 	enable();
//-----------------------------------------
//-----------------------------------------
void init_lcd()
{
	delay(15);

	wr_lcd_cw0(0x30);
	wr_lcd_cw0(0x30);
	wr_lcd_cw0(0x30);
	wr_lcd_cw0(0x20);

	wr_lcd_cw(0x28);
	wr_lcd_cw(0x0c);
	wr_lcd_cw(0x06);
	wr_lcd_cw(0x01);
}
//-----------------------------------------
void wr_lcd_cw0(unsigned char ch)
{
	delay(5);
	rs = 0;
	rw = 0;
	P0 = ((P0 & 0x0f)|(ch & 0xf0));
	enable();
}
//-----------------------------------------
void wr_lcd_cw(unsigned char ch)
{
	delay(5);
	rs=0;
	rw=0;
	P0=((P0 & 0x0f)|(ch & 0xf0));
	enable();
	P0=((P0 & 0x0f)|((ch << 4) & 0xf0));
	enable();
}
//-----------------------------------------
void wr_lcd_dw(unsigned char ch)
{
	delay(5);
	rs=1;
	rw=0;
	P0=((P0 & 0x0f)|(ch & 0xf0));
	enable();
	P0=((P0 & 0x0f)|((ch << 4) & 0xf0));
	enable();
}
//-----------------------------------------
void delay(unsigned int  time)
{
	unsigned int i,j;
	for(i=0;j<time;i++)
	for(j=0;j<120;j++);
}
//-----------------------------------------
void enable()
{
	e = 1;
	_nop_();
	_nop_();
	_nop_();
	e = 0; 
	_nop_();
	_nop_();
	_nop_();	
}
//-----------------------------------------
//-----------------------------------------
#endif
