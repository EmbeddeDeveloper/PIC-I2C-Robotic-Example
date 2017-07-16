#include <REG51F.H>
#include<stdio.h>

void uart(void);
void delay(unsigned int time);
void forward();
void reverse();
void stop();
sbit en12=P1^0;
sbit dcm1=P1^1;
sbit dcm2=P1^2;

unsigned char ch;
void main()
{
	uart();
	scanf("%c",&ch);
	switch(ch)
	{
		case 'A':
		while(1)
		{	
			 en12=1;
			 forward();
			 break;
		}
		break;
		case 'B':
		while(1)
		{
			en12=1;
			reverse();
			break;
		}
		break;
		default:
		while(1)
		{
			en12=1;
			stop();
			break;
		}
		
	}
}
void delay(unsigned int time)
{
	unsigned int i,j;
	for (i=0;i<time;i++)
	for (j=0;j<120;j++);
}
void forward()
{
	dcm1=1;
	dcm2=0;
	delay(1000);
}
void reverse()
{
	dcm1=0;
	dcm2=1;
	delay(1000);
}
void stop()
{
	dcm1=0;
	dcm2=0;
	delay(1000);
}
void uart(void)
{
	TMOD=0X20;
	TH1=0XFD;
	SCON=0X52;
	TR1=1;
}