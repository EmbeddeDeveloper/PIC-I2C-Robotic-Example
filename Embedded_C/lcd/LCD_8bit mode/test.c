#include <REG51F.H>
#include <INTRINS.H>
#define TRUE 1
#define disp P1

//sbit bl=P0^0;		//for LCD back light 
sbit rs=P3^5;		//Signal PIN
sbit rw=P3^6;		//Signal PIN
sbit en=P3^7;		//Enable PIN

void init_LCD();
void display(unsigned char signal,unsigned char cmd_data); 
void delay(unsigned int time);
void enable();
/*----beginning of main prog.-----*/
void main()
{
	init_LCD();
	display(0,0x85);
	display(1,'T');
	display(1,'I');
	display(1,'E');
	display(1,'S');

	while(TRUE);
}
//---------------------//
void init_LCD()
{
	delay(15);
	display(0,0x38);		//LCD row and column is selected
	display(0,0x0f);		//display ON and Cursor ON
	display(0,0x06);		//Increment shift cursor right side
	display(0,0x01);		//clear LCD
}
//---------------------//
void display(unsigned char signal,unsigned char cmd_data)
{
	delay(15);
	rs=signal;	//when you give signal = 0 then it work as LCD command
			// when you give signal = 1 then it work as LCD data
	rw=0;
	disp = cmd_data;
	enable();
}
//---------------------//
void enable()
{
	en=1;
	delay(1);
	en=0;

}
//---------------------//
void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<120;j++);	
}

