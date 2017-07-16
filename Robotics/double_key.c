#include <REG51F.H>

sbit sl1=P2^0;		//output for row 1
sbit sl2=P2^1;		//output for row 2
sbit sl3=P2^2;		//output for row 3
sbit sl4=P2^3;		//output for row 4

sbit krl1=P2^4;		//input for coloum 1
sbit krl2=P2^5;		//input for coloum 2
sbit krl3=P2^6;		//input for coloum 3
sbit krl4=P2^7;		//input for coloum 4

sbit en12=P1^0;		//switch for dc motor1
sbit dcm1=P1^1;		//input for dc motor1
sbit dcm2=P1^2;		//input for dc motor1

//void delay(unsigned int time);
void row1();
void row2();
void row3();
void row4();
void dc_forward();
void dc_reverse();
void dc_stop();

void main()
{
	while(1)
	{
		row1();	
		row2();	
		row3();	
		row4();	
	}
}
//--------------------------------//
void row1()
{
	sl1=0;
	if(krl1==0 && krl2==0)
	{
		dc_forward();
		P0=0x8f;
	}
	if(krl2==0 && krl3==0)
	{
		dc_reverse();
		P0=0xee;
	}
	if(krl3==0 && krl1==0)
	{
		dc_stop();
		P0=0xb6;
	}
}
//--------------------------------//
void row2()
{
	sl2=0;
	if(krl1==0 && krl2==0)
	{
		dc_forward();
		P0=0x8f;
	}
	if(krl2==0 && krl3==0)
	{
		dc_reverse();
		P0=0xee;
	}
	if(krl3==0 && krl1==0)
	{
		dc_stop();
		P0=0xb6;
	}
}
//--------------------------------//
void row3()
{
	sl3=0;
	if(krl1==0 && krl2==0)
	{
		dc_forward();
		P0=0x8f;
	}
	if(krl2==0 && krl3==0)
	{
		dc_reverse();
		P0=0xee;
	}
	if(krl3==0 && krl1==0)
	{
		dc_stop();
		P0=0xb6;
	}
}
//--------------------------------//
void row4()
{
	sl4=0;
	if(krl1==0 && krl2==0)
	{
		dc_forward();
		P0=0x8f;
	}
	if(krl2==0 && krl3==0)
	{
		dc_reverse();
		P0=0xee;
	}
	if(krl3==0 && krl1==0)
	{
		dc_stop();
		P0=0xb6;
	}
}	
//--------------------------------//
void dc_forward()
{
	en12=1;
	dcm1=1;
	dcm2=0;	
}
//--------------------------------//
void dc_reverse()
{
	en12=1;
	dcm1=0;
	dcm2=1;	
}
//--------------------------------//
void dc_stop()
{
	en12=1;
	dcm1=dcm2=0;	
}
//--------------------------------//
/*void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<120;j++);
}		 */