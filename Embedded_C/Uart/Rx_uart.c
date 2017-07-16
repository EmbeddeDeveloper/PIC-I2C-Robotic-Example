#include <REG51F.H>
void rx();
void uart();
unsigned int i;
void main()
{
	uart();	
	rx();
	for(i=0;i<=1000;i++);
	RI=0;
}
void uart()
{
	TMOD=0X20;
	TH1=0XFD;
	TR1=1;
	SCON=0X52;
}
void rx()
{
	while(!RI);
	ACC=SBUF;
	P0=ACC;
}