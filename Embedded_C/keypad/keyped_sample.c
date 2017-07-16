#include <REG51F.H>

sbit sl1=P2^0;	//row

sbit krl1=P2^4;	//coloum
sbit krl2=P2^5;
sbit krl3=P2^6;
sbit krl4=P2^7;

void main()

{
 	while(1)
	{
	  sl1=0;	//1st row selected
	  if(krl1==0)
	  P0=0xfc;

	  if(krl2==0)
	  P0=0x60;

	  if(krl3==0)
	  P0=0xda;

	  if(krl4==0)
	  P0=0xf2;

	}
}