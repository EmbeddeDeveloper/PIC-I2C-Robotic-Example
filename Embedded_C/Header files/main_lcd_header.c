#include <REG51F.H>
#include<MAIN_LCD.h>
void lcd_string(unsigned char *ptr);
void main()
{
	back=0;
	init_lcd();
	lcd_string("Ronak");
	delay(5);
	while(1);	
}

void lcd_string(unsigned char *ptr)
{
	while(*ptr!='\0')
	{
		wr_lcd_dw(*ptr);
		ptr++;
	}
}
