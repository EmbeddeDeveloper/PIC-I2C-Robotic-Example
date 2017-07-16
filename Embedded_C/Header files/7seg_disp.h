/*header file of seven segment display*/

#ifndef __SEGMENT_H__
#define __SEGMENT_H__
//--------------------------------------//
//--------------------------------------//
sbit sl1=P2^0;
sbit sl2=P2^1;
sbit sl3=P2^2;
sbit sl4=P2^3;

unsigned int ds1,ds2,ds3,ds4;
unsigned int array[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xe6};
//--------------------------------------//
//--------------------------------------//
void display();
void delay(unsigned int time);
//--------------------------------------//
//--------------------------------------//
void display()
{
	sl1=0;
	sl2=sl3=sl4=1;
	P0=arrar[ds1];
	delay(1);

	sl2=0;
	sl1=sl3=sl4=1;
	P0=array[ds2];
	delay(1);

	sl3=0;
	sl1=sl2=sl4=1;
	P0=array[ds3];
	delay(1);

	sl4=0;
	sl1=sl2=sl3=1;
	P0=array[ds4];
	delay(1);
}

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<120;j++);
}
//--------------------------------------//
//--------------------------------------//
#endif