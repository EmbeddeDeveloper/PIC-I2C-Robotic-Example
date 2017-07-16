#include<pic.h>
unsigned int i,j,k,m,u,l,d1,d2,d3,d4;
unsigned int tab[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,0xf6};
void delay1();
void delay(unsigned char i);
void display();
void delay2();
void inc();
unsigned int count=0;
void interrupt isr()
{	//RBIF=0;
	TRISB=0X00;
	PORTB=0X0C;
	delay(10);
	INTF=0;
}
void main()
{	
	
	TRISB=0X01;
	PORTB=0XF0;
	INTCON=0XD8;
	
}
void delay(unsigned char i)
{
    unsigned char j,k;
    for(j=0;j<i;j++)
	for(k=0;k<40;k++);
}
//***************************************************************/
/*
void display()
{
	//unsigned int i;
	for(k=0;k<40;k++)
	{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
		RA1=0;
		RC0=RC1=RC2=1;
		PORTB=tab[d1];
		delay1();
		RC0=0;
		RA1=RC1=RC2=1;
		PORTB=tab[d2];
		delay1();
		RC1=0;
		RA1=RC0=RC2=1;
		PORTB=tab[d3];
		delay1();
		RC2=0;
		RA1=RC0=RC1=1;
		PORTB=tab[d4];
		delay1();
	}
}
void inc()
{	
	d1++;
	if(d1==10)
	{
		d1=0;
		d2++;
	}
	if(d2==10)
	{
		d2=0;
		d3++;
	}
	if(d3==10)
	{
		d3=0;
		d4++;
	}
	if(d4==10)
	{
		d1=d2=d3=d4=0;
	}
}

	
	

void delay1()
{
	unsigned int i,j;
	for(i=0;i<=10;i++)
	for(j=0;j<=10;j++);
}
void delay2()
{
	unsigned int s,t;
	for(s=0;s<=10;s++)
	for(t=0;t<=10;t++);
}*/