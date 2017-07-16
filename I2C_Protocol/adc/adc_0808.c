#include <REG51F.H>
#include<INTRINS.H>

sbit b1=P0^0;
sbit b2=P0^1;
sbit b3=P0^2;
sbit b4=P0^3;
sbit b5=P0^4;
sbit b6=P0^5;
sbit b7=P0^6;
sbit b8=P0^7;

sbit start=P2^1;
sbit eoc=P2^2;
sbit ale=P2^3;
sbit clk=P2^4;
sbit adda=P2^5;
sbit addb=P2^6;
sbit addc=P2^7;

bit op_enable;
unsigned int out,ds1,ds2;
unsigned char arr1[]={"0123456789ABCDEF"};

void clock();
void init_uart();
void tx();
void delay(unsigned int time);

void main()
{
	init_uart();
	eoc=1;
	ale=0;
	start=0;
	op_enable=0;
	while(1)
	{
		addc=0;		//channel 0 selected
		addb=0;
		adda=0;		
		_nop_();		
		ale=1; 
		_nop_();
		start=1;
		_nop_();
		ale=0;
		start=0;
		while(eoc==1)
		{
			clock();
		}
		while(eoc==0)
		{
			clock();
		}
		_nop_();
		op_enable=1;
		_nop_();
		out=P0;
		op_enable=0;		
		B=arr1[((out&0xf0)>>4)];
		tx();
		B=arr1[((out&0x0f))];
		tx();
		delay(1000);
		B=0x0d;
		tx();
		B=0x0a;
		tx();
	}
}

void clock()
{
	clk=1;
	_nop_();
	_nop_();
	clk=0;
}

void init_uart()
{
	
	TMOD|=0x20;
	TH1=0xfd;
	TR1=1;
	SCON=0x52;
}

void tx()
{
	SBUF=B;
	while(TI==0);
	TI=0;
}

void delay(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
	for(j=0;j<120;j++);
}