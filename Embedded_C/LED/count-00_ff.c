// led blinking 00-ff//
#include <REG51F.H>
void delay(unsigned int time);
void main()
{
	unsigned char a;
	while(1)
	{
		for(a=0;a<=255;a++)
		{
		 P0=a;
		 delay(1000);
		}
	}
}

//---delay function--//
void delay(unsigned int time)
{
 unsigned int i,j;
 for(i=0;i<time;i++)
  for(j=0;j<120;j++);
}