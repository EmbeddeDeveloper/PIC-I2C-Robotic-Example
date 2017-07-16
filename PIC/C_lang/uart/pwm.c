#include<pic.h>
void init_uart();
void tx(unsigned int ch);
unsigned int ch;
void main()
{
    CCP1CON=0;
	PR2=249;
	CCPR1L=24;
	TRISC2=0;
	T2CON=0x01;
	CCP1CON=0x3c;
	TMR2=0;
	TMR2ON=1;
	while(1)
     {
        while(TMR2IF==0);
		ch=TRISC2;
		TMR2IF=0;
	 }
}
void init_uart()
{
    TXSTA=0x24;
	SPBRG=25;
	RCSTA=0x80;
}
void tx(unsigned int ch)
{
    TXREG=ch;
    while(TXIF==0);
	TXIF=0;
}
