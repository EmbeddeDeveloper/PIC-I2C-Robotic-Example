#include<pic.h>

//#define setbit(var,bit) var|=((1<<bit));
//#define clrbit(var,bit) var&=~((1<<bit));
//#define testbit(var,bit) var&=((var<<bit)&0x01);
unsigned char temp,i;
void tx();
//void rx();
void init_uart();
void delay();
void main()
{

for(i=100;i<255;i++)
{
//	init_uart();
	TXSTA=0Xb0;
	SPBRG=i;   //BAUD RATE19200  6for 9600
//RP0=0;
TXIF=1;

//RP1=0;
RCSTA=0Xa0;
temp='A';
tx();
delay();
}
//while(1)
//{
//rx();
//tx();

//}
}
//void init_uart()
//{
//RP0=1;	
	
//}

void delay()
{
	unsigned int k,l;
	for(k=0;k<1000;k++)
	for(l=0;l<40;l++);
}
void tx()
{
while(TXIF==0);

TXREG=temp;
TXIF=0;  

}
/*
void rx()
{
while((PIR1&(0x20))==0x00);

temp=RCREG;
 //clrbit(PIR1,5); 
}        */              