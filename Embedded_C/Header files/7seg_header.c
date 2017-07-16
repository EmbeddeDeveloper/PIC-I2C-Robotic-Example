#include <REG51F.H>
#include <7seg_disp.h>

void main()
{
	ds1=3;
	ds2=2;
	ds3=1;
	ds4=0;
	while(1)
	{
		display();
	}
}