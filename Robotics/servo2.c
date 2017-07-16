#include <REG51F.H>
void MSDelay(unsigned int);
/*---------------------------------------------------------------------------*/
sbit svm=P1^6;				//servo mtr is connected in port1.6
/*---------------------------------------------------------------------------*/
void main()
{	
	unsigned int i;	

	while(1)				//infinite loop 
		{
			for(i=0;i<50;i++)
			{
				svm=1;				//generating 1ms pulse repeatedly
				MSDelay(1000);
				svm=0;
				MSDelay(20);
			}
			//	MSDelay(2);
			for(i=0;i<50;i++)
			{
				svm=1;				//generating 2ms pulse repeatedly
				MSDelay(2000);
				svm=0;
			}
				MSDelay(20);
			
		}


/*	while(1)				//infinite loop 
		{
			for(i=0;i<50;i++)
			{
				svm=1;				//generating 1ms pulse repeatedly
				delay(1000);
				svm=0;
				delay_ms(20);
			}
				
			for(i=0;i<50;i++)
			{
				svm=1;				//generating 2ms pulse repeatedly
				delay(2000);
				svm=0;
				delay_ms(20);
			}
				
			
		}*/
		
		
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
