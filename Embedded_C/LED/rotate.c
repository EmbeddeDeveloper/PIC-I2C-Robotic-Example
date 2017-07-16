#include <REG51F.H>
void delay(unsigned char time);
sbit led0=P0^4;
sbit led1=P0^5;
unsigned char k;
void main()   
{ 	
	while(1)
	{	
	   	P0=0x01;
		//delay(1000);
		///P0=0x08;
		for(k=0;k<8;k++)
		{
		P0=P0<<1;
		delay(1000);
		} 
		P0=0x80;
		//delay(1000);
		for(k=0;k<8;k++)
		{
		P0=P0>>1;
		delay(1000);
		} 
		//delay(1000);					
  	}
}

void delay(unsigned char time)
{
	unsigned char i,j;
	for(j=0;j<time;j++)
	for(i=0;i<=120;i++);
}
