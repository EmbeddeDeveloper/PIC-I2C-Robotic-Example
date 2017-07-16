#include<pic.h>
void init_uart();
void tx(unsigned char ch);
unsigned char ch;
void main()
{
	TRISC=0x00;
	init_uart();
 	while(1)
	{
        	tx('U');
		while(!TRMT);
    }           
}
void init_uart()
{
	TXSTA=0xb0;
	SPBRG=103;
	RCSTA=0x80;	
}
void tx(unsigned char ch)
{
	TXREG=ch;
	while(!TXIF);
	TXIF=0;
}
