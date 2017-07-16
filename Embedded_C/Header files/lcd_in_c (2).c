#include <REG51F.H>
#include<intrins.h>
#include<LCD.H>
//--------------------------------------------
void 	init_lcd();
void 	lcd_string(unsigned char *);
//-------------------------------------------
void main()
{
	back=0;
	init_lcd();
	wr_lcd_cw(0x85);
	delay(5);
	lcd_string("Ronak");
	delay(5);
	while(1);
}

void init_lcd()
{
	delay(15);

	wr_lcd_cw0(0x30);
	wr_lcd_cw0(0x30);
	wr_lcd_cw0(0x30);
	wr_lcd_cw0(0x20);
//-----------------------
	wr_lcd_cw(0x28);
	wr_lcd_cw(0x0c);
	wr_lcd_cw(0x06);
	wr_lcd_cw(0x01);
}

void lcd_string(unsigned char *ptr)
{
	while(*ptr!='\0')
	{
	wr_lcd_dw(*ptr);
	ptr++;
	}
}
	


