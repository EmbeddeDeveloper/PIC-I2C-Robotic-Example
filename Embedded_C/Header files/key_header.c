#include <REG51F.H>
#include<key.h>
//------------------------------
//------------------------------
void init_timer0();
void isr_t0();
void display();
//------------------------------
//------------------------------
void main()
{
	init_keypad();
	init_timer0();
	EA=1;
	display();
	while(1)
	{
		while(!key_ready);
		ds1 = key_code;
		key_release();
	}
}

void init_timer0()
{
	TMOD |= 0x01;
    TH0   = 0xfc;
    TL0   = 0x66;
    TR0   = 1;
	ET0   = 1;
} 

void isr_t0()interrupt 1
{
	init_timer0();
	buzzer();
	scanner();
}

void display()
{
	ds1=15+2;
	ds2=15+2;
	ds3=15+2;
	ds4=15+2;
	delay(1000);
	ds1=15+1;
	ds2=15+1;
	ds3=15+1;
	ds4=15+1;
	delay(1000);
}
