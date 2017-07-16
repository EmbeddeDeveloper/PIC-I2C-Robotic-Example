#include <REG51F.H>
#include<LCD.h>
#include<INTRINS.H>


void init_lcd();
void delay(unsigned int time);

void main()
{

	b1=0;
	init_lcd();
	B='R';
	dw1();
	delay(5);
	B='O';
	dw1();
	delay(5);
	B='N';
	dw1();
	delay(5);
	B='A';
	dw1();
	delay(5);
	B='K';
	dw1();
	delay(5);
	B=' ';
	dw1();
	delay(5);
	B='J';
	dw1();
	delay(5);
	B='A';
	dw1();
	delay(5);
	B='I';
	dw1();
	delay(5);
	B='N';
	dw1();
	delay(5);
	while(1);
}

/*initialization of lcd...*/
void init_lcd()
{
	delay(15);
	B=0x03;
	cw();
	delay(5);
	B=0x03;
	cw();
	delay(5);
	B=0x03;
	cw();
	delay(5);
	B=0x02;
	cw();
	delay(5);
	B=0x28;
	cw();
	delay(5);
	B=0x0e;
	cw();
	delay(5);
	B=0x06;
	cw();
	delay(5);
	B=0x1c;
	cw();
	delay(5);
	B=0x01;
	cw();
	delay(5);
}

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<120;j++);
}	
