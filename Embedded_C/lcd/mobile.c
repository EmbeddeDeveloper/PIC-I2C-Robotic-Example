#include <REG51F.H>
#include<intrins.h>
#include<string.h>
//--------------------------------------------
sbit back =P0^0;
sbit rs   =P0^1;
sbit rw   =P0^2;
sbit e	  =P0^3;
sbit d4	  =P0^4;
sbit d5	  =P0^5;
sbit d6	  =P0^6;
sbit d7	  =P0^7;
//-----------------------------------------
bit c;
//------------------------------------------
void 	init_lcd();
void 	wr_lcd_cw0(unsigned char);
 void lcd_string(unsigned char *);
void 	wr_lcd_cw(unsigned char);
void 	wr_lcd_dw(unsigned char);
void 	delay_ms(unsigned int);
void    lcd_cgram_write();
void 	enable();
//-------------------------------------------

//-------------------------------------------
void main()
{
	init_lcd();
//	wr_lcd_dw('P');
	wr_lcd_cw(0x86);
  	lcd_string("BSNL");
	wr_lcd_cw(0xc2);
  	lcd_string("Charging");
 	lcd_cgram_write();
	while(1)
	{
		wr_lcd_cw(0x80);			// cursor points to display 
		wr_lcd_dw(0x00); 
	
	    wr_lcd_cw(0x81);
	    wr_lcd_dw(0x01);
	
		wr_lcd_cw(0x8f);
		wr_lcd_dw(0x02);
		delay_ms(500);
		
		wr_lcd_cw(0x8f);
		wr_lcd_dw(0x02);
		delay_ms(50);
		wr_lcd_cw(0xca);
		wr_lcd_dw(0x06);
		delay_ms(1000);
		
		wr_lcd_cw(0x8f);
		wr_lcd_dw(0x03);
	    delay_ms(50);
		wr_lcd_cw(0xcb);
		wr_lcd_dw(0x06);
		delay_ms(1000);
		
		wr_lcd_cw(0x8f);
		wr_lcd_dw(0x04);
		delay_ms(50);
		wr_lcd_cw(0xcc);
		wr_lcd_dw(0x06);
		delay_ms(1000);
		
		wr_lcd_cw(0x8f);
		wr_lcd_dw(0x05);
		delay_ms(50);
		wr_lcd_cw(0xcd);
		wr_lcd_dw(0x06);
		delay_ms(1000);

		wr_lcd_cw(0xca);
		wr_lcd_dw(0x07);
		wr_lcd_cw(0xcb);
		wr_lcd_dw(0x07);
		wr_lcd_cw(0xcc);
		wr_lcd_dw(0x07);
		wr_lcd_cw(0xcd);
		wr_lcd_dw(0x07);
		
	}
}
//-----------------------------------------
void init_lcd()
{
	delay_ms(15);

	wr_lcd_cw0(0x30);
	wr_lcd_cw0(0x30);
	wr_lcd_cw0(0x30);
	wr_lcd_cw0(0x20);
//-----------------------
	wr_lcd_cw(0x28);
	wr_lcd_cw(0x0c);
	wr_lcd_cw(0x06);
	wr_lcd_cw(0x01);
	back = 0;
 	
}
//-----------------------------------
void wr_lcd_cw0(unsigned char ch)
{
	delay_ms(5);
	rs = 0;
	rw = 0;
	P0 = ((P0 & 0x0f)|(ch & 0xf0));
	enable();
}

//-----------------------------------
void wr_lcd_cw(unsigned char ch)
{
	delay_ms(5);
	rs = 0;
	rw = 0;
	P0 = ((P0 & 0x0f)|(ch & 0xf0));
	e = 1;
	_nop_();
	_nop_();
	_nop_();
	e = 0; 	

	P0 = ((P0 & 0x0f)|((ch << 4) & 0xf0));
	e = 1;
	_nop_();
	_nop_();
	_nop_();
	e = 0; 	


}

//-----------------------------------
void wr_lcd_dw(unsigned char ch)
{
	delay_ms(5);
	rs = 1;
	rw = 0;
	P0 = ((P0 & 0x0f)|(ch & 0xf0));
	e = 1;
	_nop_();
	_nop_();
	_nop_();
	e = 0; 	

	P0 = ((P0 & 0x0f)|((ch << 4) & 0xf0));
	e = 1;
	_nop_();
	_nop_();
	_nop_();
	e = 0; 	
}

void delay_ms(unsigned int  i)
{
	unsigned int j,k;
	for(j = 0; j <= i; j++)
	{
		for(k = 0; k <= 120; k++);
	}
}
//-----------------------------------------------------------------------------

void lcd_cgram_write()
{
	wr_lcd_cw(0x40);	  	// cursor points in CGRAM
//----------------------------------------------------- 
	wr_lcd_dw(0x1c);
	wr_lcd_dw(0x1c);
	wr_lcd_dw(0x10);
	wr_lcd_dw(0x11);
	wr_lcd_dw(0x15);
	wr_lcd_dw(0x15);
	wr_lcd_dw(0x15);
	wr_lcd_dw(0x00);
//------------------------------------------------------
	wr_lcd_dw(0x01);
	wr_lcd_dw(0x05);
	wr_lcd_dw(0x15);
	wr_lcd_dw(0x15);
	wr_lcd_dw(0x15);
	wr_lcd_dw(0x15);
	wr_lcd_dw(0x15);
	wr_lcd_dw(0x00);
//-------------------------------------------
	wr_lcd_dw(0x0e);
	wr_lcd_dw(0x1b);
	wr_lcd_dw(0x11);
	wr_lcd_dw(0x11);
	wr_lcd_dw(0x11);
	wr_lcd_dw(0x11);
	wr_lcd_dw(0x11);
	wr_lcd_dw(0x1f);
//-------------------------------------------------
	wr_lcd_dw(0x0e);
	wr_lcd_dw(0x1b);
	wr_lcd_dw(0x11);
	wr_lcd_dw(0x11);
	wr_lcd_dw(0x11);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
//------------------------------------------------
	wr_lcd_dw(0x0e);
	wr_lcd_dw(0x1b);
	wr_lcd_dw(0x11);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
//----------------------------------------------
	wr_lcd_dw(0x0e);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
	wr_lcd_dw(0x1f);
//----------------------------------
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x0c);
	wr_lcd_dw(0x0c);
	wr_lcd_dw(0x00);
//------------------------------------------
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
	wr_lcd_dw(0x00);
}
//----------------------------------------------------

//--------------------------------------------------
void enable()
{
	e = 1;
	_nop_();
	_nop_();
	_nop_();
	e = 0; 	
}
 void lcd_string(unsigned char *ptr)
{
	while(*ptr!='\0')
	{
	wr_lcd_dw(*ptr);
	ptr++;
	}
}
	
