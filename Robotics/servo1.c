#include <REG51F.H>
void MSDelay(unsigned int);
/*---------------------------------------------------------------------------*/
sbit svm=P1^6;				//servo mtr is connected in port1.6
/*---------------------------------------------------------------------------*/
void main()
{		

	while(1)				//infinite loop 
		{
			svm=1;
			MSDelay(1);
			svm=0;
			MSDelay(2);
			svm=1;
			MSDelay(2);
			svm=0;
			MSDelay(2);
			
		}
		
}
/*---------------------------------------------------------------------------*/
void MSDelay(unsigned int itime)
{
	unsigned int i,j;
	for(i=0;i<itime;i++)
	{
	j++;
	}
}